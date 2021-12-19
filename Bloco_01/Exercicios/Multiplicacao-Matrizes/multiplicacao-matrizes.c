#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define VALOR_INVALIDO_SEMENTE -1

int main()
{
    // ENTRADAS  
    long int nLinhasA, nColunasA;
    scanf("%ld %ld\n", &nLinhasA, &nColunasA); // Entrada 1: dimensões A

    long int nLinhasB, nColunasB;
    scanf("%ld %ld\n", &nLinhasB, &nColunasB); // Entrada 2: dimensões B

    if (nColunasA != nLinhasB)
    {
        printf("Valores invalidos para a multiplicacao.\n");
        exit(0); // Interrompe caso as dimensões sejam incompatíveis.
    }

    int semente = VALOR_INVALIDO_SEMENTE;
    scanf("%d", &semente); // Entrada 3: semente

    if (feof(stdin))
    {
        printf("Valores invalidos para a multiplicacao.\n");
        exit(0); // Interrompe caso não tenha recebido a semente (seed).
    }

    srand(semente); // Definição da semente do gerador ANTES de ele ser utilizado.

    // GERAR MATRIZES
    long int matrizA[nLinhasA][nColunasA]; 
    long int matrizB[nLinhasB][nColunasB];
    long int matrizC[nLinhasA][nColunasB];
  
    for (int i = 0; i < nLinhasA; i++) // MATRIZ A
    {   
        for (int j = 0; j < nColunasA; j++)
            matrizA[i][j] = rand()%50 - 25; // Gera um número aleatório entre -25 e 24.
    }

    for (int i = 0; i < nLinhasB; i++) // MATRIZ B   
    {
        for (int j = 0; j < nColunasB; j++)
            matrizB[i][j] = rand() % 50 - 25;
    }

    // MULTIPLICAR E IMPRIMIR
    for (int i = 0; i < nLinhasA; i++) // Vai passar por todas as linhas de C.
    {
        printf("Linha %d: ", i);
        for (int j = 0; j < nColunasB; j++) // Vai passar por cada elemento da linha de C.
        {
            matrizC[i][j] = 0;
            for (int k = 0; k < nColunasA; k++)
            {
                matrizC[i][j] += matrizA[i][k] * matrizB[k][j]; 
            }
            printf("%ld ", matrizC[i][j]);
        }
        printf("\n");
    }

    return 0;
}