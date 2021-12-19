#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define HLT 0   // HALT: parada
#define ADD 1   // ADD: soma dois elementos e escreve o resultado
#define MUL 2   // MULTIPLY: multiplica dois elementos e escreve o resultado
#define CLT 3   // COMPARE LESS THAN: verifica se o primeiro inteiro é menor que o segundo e escreve true/false
#define CEQ 4   // COMPARE EQUALS: verifica se dois inteiros são iguais e escreve true/false
#define JMP 5   // JUMP: altera o ponteiro de execução
#define JEQ 6   // JUMP IF EQUAL: alteração condicional do ponteiro de execução
#define CPY 7   // COPY: copia o valor de um endereço para outro endereço
#define PUT 8   // PUT: imprime um caractere na saída (a partir do valor dado no endereço fornecido)
#define PTN 9   // PUT NUM: imprime um inteiro na saída (encontrado no endereço fornecido)

#define TAMANHO_FITA 512

int main()
{
    // ENTRADA DA FITA
    int fita[TAMANHO_FITA];

    for (int i = 0; i < TAMANHO_FITA; i++)
    {
        scanf("%d\n", &fita[i]);
    }

    printf("Saida do programa:\n");

    // EXECUÇÃO DA FITA
    int ponteiro = 0;
    while (ponteiro < TAMANHO_FITA)
    {
        if (fita[ponteiro] == HLT)
        {
            ponteiro = TAMANHO_FITA;
        }

        else if (fita[ponteiro] == ADD)
        {
            ponteiro++;
            int endereco1 = fita[ponteiro];
            ponteiro++;
            int endereco2 = fita[ponteiro];
            ponteiro++;
            int destino = fita[ponteiro];

            int add = fita[endereco1] + fita[endereco2];
            fita[destino] = add;

            ponteiro++;
        }

        else if (fita[ponteiro] == MUL)
        {
            ponteiro++;
            int endereco1 = fita[ponteiro];
            ponteiro++;
            int endereco2 = fita[ponteiro];
            ponteiro++;
            int destino = fita[ponteiro];

            int mul = fita[endereco1] * fita[endereco2];
            fita[destino] = mul;

            ponteiro++;
        }

        else if (fita[ponteiro] == CLT)
        {
            ponteiro++;
            int endereco1 = fita[ponteiro];
            ponteiro++;
            int endereco2 = fita[ponteiro];
            ponteiro++;
            int destino = fita[ponteiro];

            if (fita[endereco1] < fita[endereco2])
                fita[destino] = TRUE;
            else
                fita[destino] = FALSE;

            ponteiro++;
        }

        else if (fita[ponteiro] == CEQ)
        {
            ponteiro++;
            int endereco1 = fita[ponteiro];
            ponteiro++;
            int endereco2 = fita[ponteiro];
            ponteiro++;
            int destino = fita[ponteiro];

            if (fita[endereco1] == fita[endereco2])
                fita[destino] = TRUE;
            else
                fita[destino] = FALSE;

            ponteiro++;
        }

        else if (fita[ponteiro] == JMP)
        {
            ponteiro++;
            int endereco1 = fita[ponteiro];

            ponteiro = fita[endereco1];
        }

        else if (fita[ponteiro] == JEQ)
        {
            ponteiro++;
            int endereco1 = fita[ponteiro];
            ponteiro++;
            int endereco2 = fita[ponteiro];

            if (fita[endereco1] != FALSE)
                ponteiro = fita[endereco2];
            else
                ponteiro++;  
        }

        else if (fita[ponteiro] == CPY)
        {
            ponteiro++;
            int endereco1 = fita[ponteiro];
            ponteiro++;
            int destino = fita[ponteiro];

            fita[destino] = fita[endereco1];

            ponteiro++;
        }

        else if (fita[ponteiro] == PUT)
        {
            ponteiro++;
            int endereco1 = fita[ponteiro];

            printf("%c", fita[endereco1]);

            ponteiro++;
        }

        else if (fita[ponteiro] == PTN)
        {
            ponteiro++;
            int endereco1 = fita[ponteiro];

            printf("%d", fita[endereco1]);

            ponteiro++;
        }
    }
    
    // SAÍDA (continuação)
    printf("\n");
    printf("Estado final da fita:\n");
    for (int i = 0; i < TAMANHO_FITA; i++)
    {
        printf("%d\n", fita[i]);
    }

    return 0;
}