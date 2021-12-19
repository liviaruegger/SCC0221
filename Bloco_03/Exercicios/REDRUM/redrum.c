#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

char *adapted_readline();
char *remove_char(char *string, char discard);

bool  is_palindrome(char *string);
bool _is_palindrome(char *string, int left, int right);

int main()
{
    char *string = adapted_readline();

    bool is_direct_palindrome = is_palindrome(string);

    if (is_direct_palindrome == true)
    {
        printf("Palindromo direto\n");
    }
    else
    {
        string = remove_char(string, ' ');
        string = remove_char(string, '/');

        bool is_indirect_palindrome = is_palindrome(string);

        if (is_indirect_palindrome == true)
            printf("Palindromo indireto\n");
        else
            printf("Nao eh um palindromo\n");
    }

    free(string);

    return 0;
}

// Lê uma string da entrada padrão, já descartando os caracteres que não são alfanuméricos
// ou ' ' (espaço) ou '/' (barra) e trocando maiúsculas por minúsculas.
// Retorna o ponteiro para essa string.
char *adapted_readline()
{
    char *string = (char *) malloc(sizeof(char));
    int string_size = 0;

    do
    {
        char temp = fgetc(stdin);

        bool is_alphanum = isalnum(temp);

        if (is_alphanum != false || temp == ' ' || temp == '/' || temp == '\n')
        {
            temp = tolower(temp);
            string[string_size] = temp;
            string_size++;

            if (string[string_size - 1] != '\n')
                string = (char *) realloc(string, string_size + 1);
        }

    } while (string[string_size - 1] != '\n');

    string[string_size - 1] = '\0';

    return string;
}

// Recebe uma string por referência e um caractere.
// Caso haja ocorrência do caractere na string, cria uma cópia sem esse caractere,
// desaloca a string original e retorna o ponteiro para a nova versão.
// Caso não haja, retorna o ponteiro original.
char *remove_char(char *string, char discard)
{
    const char discard_str[1] = {discard};
    if (strstr(string, discard_str) == NULL)
        return string;

    int string_size = strlen(string) + 1;
    char *temp_string = (char *) malloc(string_size);
    int temp_string_size = 0;

    for (int i = 0; i < string_size; i++)
    {
        if (string[i] != discard)
            temp_string[temp_string_size++] = string[i];
    }

    free(string);

    temp_string = (char *) realloc(temp_string, temp_string_size);

    return temp_string;
}

// Função recebe apenas o ponteiro para a string e chama a função recursiva com os
// parâmetros adequados (a string, zero, e o índice do último caractere da string).
bool is_palindrome(char *string)
{
    return _is_palindrome(string, 0, strlen(string) - 1);
}

// Função recursiva que checa se uma string é um palíndromo ou não.
// Recebe uma string por referência e dois índices para comparação (esquerda e direita).
// Retorna true (é palíndromo) ou false (não é palíndromo).
bool _is_palindrome(char *string, int left, int right)
{
    // Se chegou ao meio, a string é palíndromo.
    if (left >= right)
        return true;

    // Se os caracteres de início e fim são diferentes, a string não é palíndromo.
    if (string[left] != string[right])
        return false;

    // Se não chegou ao meio e os caracteres comparados são iguais,
    // continua checando se o que está no meio é palíndromo.
    return _is_palindrome(string, left + 1, right - 1);
}