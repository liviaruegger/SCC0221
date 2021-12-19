#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 50

/* Para a leitura das linhas, o seu programa deverá implementar uma função
char *read_line() que lê uma string, caractere por caractere, da entrada
padrão, alocando dinamicamente memória para armazenamento, até encontrar
um ’\n’ e retornar o resultado. */

char *read_line(char end_char)
{
    char *line = (char *) malloc(BUFFER_SIZE);

    int max_size = BUFFER_SIZE;
    int free_memory = max_size;
    int string_size = 0;
    char c;

    do
    {
        c = fgetc(stdin); // Neste caso, funciona da mesma forma que c = getchar()

        free_memory--;
        if (free_memory == 0) // Aumenta o espaço de memória alocada quando necessário.
        {
            free_memory = BUFFER_SIZE; // Reseta a contagem de espaço livre.
            max_size += BUFFER_SIZE;   // Aumenta o espaço total.
            line = (char *) realloc(line, max_size); // Realoca.
        }

        line[string_size] = c;
        string_size++;

    } while (c != end_char);

    line[string_size - 1] = '\0'; // Substitui o end_char por '\0'

    line = (char *) realloc(line, string_size); // Redimensiona a string.
    
    return line;
}

int main()
{
    // ENTRADA: número n > 0 de linhas
    int n;
    scanf("%d\n", &n);

    // ENTRADA: n linhas
    char *line_ptr[n];
    for (int i = 0; i < n; i++)
        line_ptr[i] = (char *) read_line('\n');

    // ENTRADA: número v de linhas válidas, sendo 0 < v <= n
    int v; 
    scanf("%d\n", &v);

    // ENTRADA: v índices que indentificam as linhas válidas, sendo 0 <= i <= n
    int index[v];
    for (int i = 0; i < v; i++)
        scanf(" %d", &index[i]);
    
    // SAÍDA: v linhas válidas separadas por um '\n'
    for (int i = 0; i < v; i++)
        printf("%s\n", line_ptr[index[i]]);
    
    // LIMPAR MEMÓRIA
    for (int i = 0; i < n; i++)
        free(line_ptr[i]); 
    
    return 0;
}