#include <stdio.h>
#include <stdlib.h>

int main()
{
    /* A entrada começará com um número inteiro n, que pode ser lido com scanf.
    Esse inteiro representará a altura do triângulo em questão. Além dele, será
    dado em seguida um caractere qualquer c correspondente ao caractere do qual
    o triângulo será formado. */

    int n; // O valor de n deve ser tal que 0 < n <= 25
    char c;

    scanf(" %i %c", &n, &c);

    if (n <= 0 || n > 25)
    {
        printf("Altura invalida\n");
        exit(0); // Encerra o programa imediatamente.
    }

    /* Tentando entender como funciona o triângulo.

        Para n = 4:

        e = n - 1

                X       => e          espaços  +  t      char
               XXX      => e--        espaços  +  t += 2 char
              XXXXX     => e--        espaços  +  t += 2 char
             XXXXXXX    => e-- (zero) espaços  +  t += 2 char

    */

    int e, i;  // Número de espaços na linha do triângulo, contador caracteres.
    int t = 1; // Número de caracteres na linha do triângulo.

    // Lembrando que: for(valor_inicial; condição; incremento)
    for (; n > 0; n--) // Este for roda 1 vez para cada linha.
    {
        for (e = n - 1; e > 0; e--) // Em função de e. Quando o for termina:
            printf(" ");            // imprimiu o número certo de espaços; e = 0

        for (i = t; i > 0; i--)
            printf("%c", c);

        printf("\n");
        t = t + 2;
    }

    return 0;
}