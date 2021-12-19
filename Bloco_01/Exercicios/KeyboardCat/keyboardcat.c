#include <stdio.h>

int main()
{
    // INPUT //
    char keyboard[49], mensagem;
    int n, i, posicao;
    
    // Sequência de chars:
    for (i = 0; i < 49; i++)
    {
        scanf(" %c", &keyboard[i]); 
    }

    // Tamanho da mensagem:
    scanf(" %i", &n); 

    // Sequência codificada:
    int codificada[n];
    for (i = 0; i < n; i++)
    {
        scanf(" %i", &codificada[i]); 
    }

    // OUTPUT //
    for (i = 0; i < n; i++)
    {
        posicao = codificada[i];
        mensagem = keyboard[posicao];

        // O caractere ' ' (espaço) é representado por um '_' (underline/underscore) no sistema do teclado;
        // O caractere '\n' (quebra de linha) é representado por um 'E' (e maiúsculo) no sistema do teclado.

        if (mensagem == 'E') // Para comparação usar ' ' e não " "
            printf("\n");
        else if (mensagem == '_')
            printf(" ");
        else
            printf("%c", mensagem);
    }
    
    return 0;
}