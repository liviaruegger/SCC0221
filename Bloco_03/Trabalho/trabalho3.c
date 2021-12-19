#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct fill
{
    char color;
    int  start_i;
    int  start_j;
}   fill_t;

char  *read_line(FILE *stream, bool *is_eof);
char **read_matrix(FILE *stream, int *n_lines);

int  string_lengh(char *string);
void fill_area(char **art_matrix, int n_lines, fill_t fill);
void fill_pixel(char **art_matrix, int n_lines, char start_color, char color, int i, int j);
void print_art(FILE *output, char **art_matrix, int n_lines);
void free_matrix(char **art_matrix, int n_lines);

void enquadra_arte(
    char *nome_do_arquivo_da_arte,
    int altura_do_quadro,
    int largura_do_quadro);

int main()
{
    bool  discard;
    char *art_file_name = read_line(stdin, &discard);

    int n_fillings;
    scanf("%d\n", &n_fillings);

    fill_t fillings[n_fillings];

    for (int i = 0; i < n_fillings; i++)
    {
        scanf("%c", &fillings[i].color);
        scanf(" %d", &fillings[i].start_i);
        scanf(" %d\n", &fillings[i].start_j);
    }

    FILE *art_file = fopen(art_file_name, "r");
    int n_lines;
    char **art_matrix = read_matrix(art_file, &n_lines);
    fclose(art_file);

    printf("Arte inicial:\n");
    print_art(stdout, art_matrix, n_lines);

    for (int i = 0; i < n_fillings; i++)
    {
        fill_area(art_matrix, n_lines, fillings[i]);
        printf("\n\nArte apos a etapa %d:\n", i);
        print_art(stdout, art_matrix, n_lines);
    }

    art_file = fopen(art_file_name, "w");
    print_art(art_file, art_matrix, n_lines);
    fclose(art_file);
    
    printf("\n\nArte enquadrada:\n");
    int line_size = string_lengh(art_matrix[0]);
    enquadra_arte(art_file_name, n_lines, line_size);

    free_matrix(art_matrix, n_lines);
    free(art_file_name);

    return 0;
}

// Lê e armazena uma linha do arquivo dado até encontrar o fim da linha ou do arquivo.
// Retorna o ponteiro para essa linha salva e confirma se atingiu ou não o fim do arquivo.
char *read_line(FILE *stream, bool *is_eof)
{
    char *string = (char *) malloc(sizeof(char));
    int string_size = 0;

    do
    {
        string[string_size] = fgetc(stream);
        string_size++;

        if (string[string_size - 1] != '\n' && string[string_size - 1] != EOF)
            string = (char *) realloc(string, string_size + 1);

    } while (string[string_size - 1] != '\n' && string[string_size - 1] != EOF);

    if (string[string_size - 1] == EOF)
        *is_eof = true;

    string[string_size - 1] = '\0';

    return string;
}

// Lê e armazena uma matriz do arquivo passado como parâmetro até encontrar EOF.
// Retorna o ponteiro para essa matriz salva e a quantidade de linhas que ela contém.
char **read_matrix(FILE *stream, int *n_lines)
{
    char **art_matrix = NULL; 
    char  *new_line   = NULL;
    
    bool is_eof = false;
    int  line_count = 0;

    do
    {
        art_matrix = (char **) realloc(art_matrix, (line_count + 1) * sizeof (char *));

        new_line = read_line(stream, &is_eof);
        art_matrix[line_count++] = new_line; 
        
    } while (is_eof == false);

    *n_lines = line_count;
    
    return art_matrix;
}

// Conta a quantidade de caracteres em uma string.
int string_lengh(char *string)
{
    int count = 0;

    while (string[count] != '\0')
        count++;

    return count;
}

// Chama a função recursiva de preenchimento a partir do pixel inicial.
void fill_area(char **art_matrix, int n_lines, fill_t fill)
{
    char start_color = art_matrix[fill.start_i][fill.start_j];
    fill_pixel(art_matrix, n_lines, start_color, fill.color, fill.start_i, fill.start_j);
}

// Função recursiva que altera o pixel dado caso ele seja pintável (caractere inicial).
void fill_pixel(char **art_matrix, int n_lines, char start_color, char color, int i, int j)
{
    // Checa se o pixel está dentro da matriz.
    if (i < 0 || i >= n_lines)
        return;
    int line_size = string_lengh(art_matrix[i]);
    if (j < 0 || j >= line_size)
        return;
    
    // Se o pixel dado não for pintável, encerra.
    if(art_matrix[i][j] != start_color)
        return;

    // Pinta o pixel. 
    art_matrix[i][j] = color;
    
    // Chama a função para os vizinhos.
    fill_pixel(art_matrix, n_lines, start_color, color, i - 1, j);
    fill_pixel(art_matrix, n_lines, start_color, color, i, j - 1);
    fill_pixel(art_matrix, n_lines, start_color, color, i, j + 1);
    fill_pixel(art_matrix, n_lines, start_color, color, i + 1, j);
}

// Imprime a arte no output passado como parâmetro.
void print_art(FILE *output, char **art_matrix, int n_lines)
{
    for (int i = 0; i < n_lines - 1; i++)
        fprintf(output, "%s\n", art_matrix[i]);
    fprintf(output, "%s", art_matrix[n_lines - 1]);
}

// Desaloca a memória utilizada pela matriz da arte.
void free_matrix(char **art_matrix, int n_lines)
{
    for (int i = 0; i < n_lines; i++)
        free(art_matrix[i]);
    free(art_matrix);
}

// Função auxiliar (feita pelo monitor).
void enquadra_arte(
    char *nome_do_arquivo_da_arte,
    int altura_do_quadro,
    int largura_do_quadro
)
{
    FILE *f_arte_ptr = fopen(nome_do_arquivo_da_arte, "r");
    if (f_arte_ptr == NULL)
    {
        printf(
            "Erro na abertura do arquivo, "
            "Você esqueceu de fechar o arquivo antes? "
            "Ou deu free na string com o nome sem querer?\n"
        );

        exit(EXIT_FAILURE);
    }

    int qtd_espc_comeco;
    const char *apoio;
    if (largura_do_quadro % 2 == 0)
    {
        qtd_espc_comeco = largura_do_quadro / 2;
        apoio = "/\\";
    }
    else
    {
        qtd_espc_comeco = largura_do_quadro / 2 + 1;
        apoio = "Ʌ";
    }

    for (int i = 0; i < qtd_espc_comeco; i++)
        printf(" ");
    printf("%s\n", apoio);

    printf("╭");
    for (int i = 0; i < largura_do_quadro; i++)
        printf("—");
    printf("╮\n");

    for (int i = 0; i < altura_do_quadro; i++)
    {
        printf("|");
        for (int j = 0; j < largura_do_quadro; j++)
        {
            char pixel_atual = fgetc(f_arte_ptr);
            printf("%c", pixel_atual);
        }
        printf("|");

        char quebra = fgetc(f_arte_ptr);
        if (quebra != EOF)
            printf("%c", quebra);
    };
    fclose(f_arte_ptr);

    printf("\n╰");
    for (int i = 0; i < largura_do_quadro; i++)
        printf("—");
    printf("╯\n");
}