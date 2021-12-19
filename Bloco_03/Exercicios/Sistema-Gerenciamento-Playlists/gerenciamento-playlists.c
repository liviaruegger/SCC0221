#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADICIONAR_MUSICA  1
#define EXIBIR_PLAYLIST   2
#define PROXIMA           3
#define VOLTAR            4
#define SALVAR_PLAYLIST   5
#define CARREGAR_PLAYLIST 6
#define FINALIZAR         7

#define N_MAX_MUSICAS 15

typedef struct musica
{
    char *nome;
    char *artista;
    int   duracao;
} musica_t;

typedef struct playlist
{
    char      *nome;
    musica_t **musicas;
    int        n_musicas;
    int        em_execucao;
} playlist_t;

char     *ler_string();
musica_t *ler_musica();

void adicionar_musica(playlist_t *);
void exibir_playlist(playlist_t *);
void salvar_playlist(playlist_t *);
void carregar_playlist(playlist_t *);

void limpar_musica(musica_t *);
void limpar_playlist(playlist_t *);

void binary_to_num(char *);

int main()
{
    // CRIAR PLAYLIST (vazia)
    playlist_t *playlist = (playlist_t *) malloc(sizeof(playlist_t));
    playlist->musicas    = (musica_t **)  malloc(N_MAX_MUSICAS * sizeof(musica_t *));
    playlist->nome       = ler_string();
    playlist->n_musicas  = 0;

    // LER E EXECUTAR COMANDOS
    int comando;
    do
    {
        scanf("%d ", &comando);

        if (comando == ADICIONAR_MUSICA)
            adicionar_musica(playlist);
        else if (comando == EXIBIR_PLAYLIST)
            exibir_playlist(playlist);
        else if (comando == PROXIMA)
            playlist->em_execucao++;
        else if (comando == VOLTAR)
            playlist->em_execucao--;
        else if (comando == SALVAR_PLAYLIST)
            salvar_playlist(playlist);
        else if (comando == CARREGAR_PLAYLIST)
            carregar_playlist(playlist);
            
    } while (comando != FINALIZAR);

    // LIMPAR MEMÓRIA
    limpar_playlist(playlist);

    return 0;
}

// Lê e armazena uma string da entrada padrão.
// Retorna um ponteiro para essa string.
char *ler_string()
{
    char *string = (char *) malloc(sizeof(char));
    int tamanho = 0;

    do
    {
        string[tamanho] = fgetc(stdin);
        tamanho++;

        if (string[tamanho - 1] != '\n')
            string = (char *) realloc(string, tamanho + 1);

    } while (string[tamanho - 1] != '\n');

    string[tamanho - 1] = '\0';

    return string;
}

// Lê e armazena uma música (struct) da entrada padrão.
// Retorna um ponteiro para essa música.
musica_t *ler_musica()
{
    musica_t *musica_temp = (musica_t *) malloc(sizeof(musica_t));

    musica_temp->nome    = ler_string();
    musica_temp->artista = ler_string();
    scanf("%d ", &musica_temp->duracao);
  
    return musica_temp;
}

// Se couber, adiciona música à playlist.
void adicionar_musica(playlist_t *playlist)
{
    if (playlist->n_musicas < N_MAX_MUSICAS)
    {
        musica_t *musica = ler_musica();
        playlist->musicas[playlist->n_musicas] = musica;
        playlist->n_musicas++;

        printf("Musica %s de %s adicionada com sucesso.\n", musica->nome, musica->artista);

        if (playlist->n_musicas == 1)
            playlist->em_execucao = 0;
    }
    else
    {
        printf("Playlist cheia!\n");
    }
}

// Imprime informações sobre a playlist.
void exibir_playlist(playlist_t *playlist)
{
    printf("---- Playlist: %s ----\n", playlist->nome);
    printf("Total de musicas: %d\n\n", playlist->n_musicas);

    for (int i = 0; i < playlist->n_musicas; i++)
    {
        if (i == playlist->em_execucao)
            printf("=== NOW PLAYING ===\n");

        printf("(%d). '%s'\n", i + 1, playlist->musicas[i]->nome);
        printf("Artista: %s\n", playlist->musicas[i]->artista);
        printf("Duracao: %d segundos\n\n", playlist->musicas[i]->duracao);
    }
}

// Salva a playlist atual em um arquivo binário (com nome lido da entrada padrão).
void salvar_playlist(playlist_t *playlist)
{
    char *nome_arquivo = ler_string();

    FILE *arquivo = fopen(nome_arquivo,"wb");
    
    // CABEÇALHO PLAYLIST
    // 4 bytes | tamanho do nome da playlist
    // string  | nome da playlist 
    // 4 bytes | numero de musicas

    int tamanho_string = strlen(playlist->nome);
    fwrite(&tamanho_string, sizeof(int), 1, arquivo);
    fwrite(playlist->nome, sizeof(char), tamanho_string, arquivo);
    fwrite(&playlist->n_musicas, sizeof(int), 1, arquivo);

    // ESTRUTURA DO REGISTRO DE MÚSICA
    // 4 bytes | tamanho do nome da música
    // string  | nome da música
    // 4 bytes | tamanho do nome do artista
    // string  | nome do artista
    // 4 bytes | duração da música

    for (int i = 0; i < playlist->n_musicas; i++)
    {
        tamanho_string = strlen(playlist->musicas[i]->nome);
        fwrite(&tamanho_string, sizeof(int), 1, arquivo);
        fwrite(playlist->musicas[i]->nome, sizeof(char), tamanho_string, arquivo);

        tamanho_string = strlen(playlist->musicas[i]->artista);
        fwrite(&tamanho_string, sizeof(int), 1, arquivo);
        fwrite(playlist->musicas[i]->artista, sizeof(char), tamanho_string, arquivo);

        fwrite(&playlist->musicas[i]->duracao, sizeof(int), 1, arquivo);
    }
    fclose(arquivo);
    printf("Playlist %s salva com sucesso.\n", nome_arquivo);

    binary_to_num(nome_arquivo);
    free(nome_arquivo);
}

// Carrega uma nova playlist a partir de um arquivo binário.
void carregar_playlist(playlist_t *playlist)
{
    char *nome_arquivo = ler_string();

    FILE *arquivo = NULL;
    arquivo = fopen(nome_arquivo,"rb");

    if (arquivo == NULL)
    {
        printf("Arquivo %s nao existe.\n", nome_arquivo);
        limpar_playlist(playlist);
        free(nome_arquivo);
        exit(0);
    }

    // Liberar memória para uma nova playlist.
    // Obs: mantém o mesmo ponteiro da playlist anterior.
    free(playlist->nome);
    for (int i = 0; i < playlist->n_musicas; i++)
        limpar_musica(playlist->musicas[i]);

    playlist->em_execucao = 0;
    
    // CABEÇALHO PLAYLIST
    // 4 bytes | tamanho do nome da playlist
    // string  | nome da playlist 
    // 4 bytes | numero de musicas

    int tamanho_string;

    fread(&tamanho_string, sizeof(int), 1, arquivo);
    playlist->nome = (char *) malloc((tamanho_string + 1) * sizeof(char));
    fread(playlist->nome, sizeof(char), tamanho_string, arquivo);
    playlist->nome[tamanho_string] = '\0';
    
    fread(&playlist->n_musicas, sizeof(int), 1, arquivo);

    // ESTRUTURA DO REGISTRO DE MÚSICA
    // 4 bytes | tamanho do nome da música
    // string  | nome da música
    // 4 bytes | tamanho do nome do artista
    // string  | nome do artista
    // 4 bytes | duração da música

    for (int i = 0; i < playlist->n_musicas; i++)
    {
        playlist->musicas[i] = (musica_t *) malloc(sizeof(musica_t));

        fread(&tamanho_string, sizeof(int), 1, arquivo);
        playlist->musicas[i]->nome = (char *) malloc((tamanho_string + 1) * sizeof(char));
        fread(playlist->musicas[i]->nome, sizeof(char), tamanho_string, arquivo);
        playlist->musicas[i]->nome[tamanho_string] = '\0';

        fread(&tamanho_string, sizeof(int), 1, arquivo);
        playlist->musicas[i]->artista = (char *) malloc((tamanho_string + 1) * sizeof(char));
        fread(playlist->musicas[i]->artista, sizeof(char), tamanho_string, arquivo);
        playlist->musicas[i]->artista[tamanho_string] = '\0';

        fread(&playlist->musicas[i]->duracao, sizeof(int), 1, arquivo);
    }
    fclose(arquivo);
    printf("Playlist %s carregada com sucesso.\n", nome_arquivo);
    
    binary_to_num(nome_arquivo);
    free(nome_arquivo);
}

// Limpa a memória utilizada para armazenar uma música.
void limpar_musica(musica_t *musica_ptr)
{
    free(musica_ptr->nome);
    free(musica_ptr->artista);
    free(musica_ptr);
}

// Limpa a memória utilizada para armazenar a playlist.
void limpar_playlist(playlist_t *playlist)
{
    free(playlist->nome);
    for (int i = 0; i < playlist->n_musicas; i++)
        limpar_musica(playlist->musicas[i]);
    free(playlist->musicas);
    free(playlist);
}

// Soma polinomial que interpreta o valor binário como um valor numérico.
// Quanto mais próximo o valor de retorno, mais próximo seu binário está do ideal.
// Não há necessidade de entender o funcionamento dessa função.
//
// Parâmetros: Nome do arquivo (binFilename: char *)
// Retorno: Nada (void)
void binary_to_num(char *binFilename)
{
    FILE *fp = fopen(binFilename, "rb");

    double binValue = 0;
    double accumulator = 0.01;
    char ch;
    while (fread(&ch, sizeof(char), 1, fp))
    {
        binValue += (double) ch * accumulator;
        accumulator += 0.01;
    }

    fclose(fp);
    printf("%lf\n", binValue);
}