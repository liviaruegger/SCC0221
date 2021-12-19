#include <stdio.h>
#include <stdlib.h>

#define       MOORE 'M'
#define VON_NEUMANN 'N'

#define  VIVA 'x'
#define MORTA '.'

void erro()
{
    printf("Dados de entrada apresentam erro.\n");
    exit(0);
}

char **ler_matriz(int n_linhas, int n_colunas)
{
    // Alocar memória para a matriz:
    char **matriz = (char **) malloc(n_linhas * sizeof(char *));
    for (int i = 0; i < n_linhas; i++)
        matriz[i] = (char *) malloc(n_colunas * sizeof(char));

    // Receber matriz da entrada:
    for (int i = 0; i < n_linhas; i++)
    {
        for (int j = 0; j < n_colunas; j++)
            scanf("%c", &matriz[i][j]);
        scanf("%*[\n]s");
    }

    return matriz;
}

void limpar_matriz(char **matriz, int n_linhas)
{
    for (int i = 0; i < n_linhas; i++)
        free(matriz[i]);
    free(matriz);
}

int contar_vizinhos_vivos(char **matriz, int n_linhas, int n_colunas, char vizinhanca, int i, int j)
{
    int n_celulas_vivas = 0;
    int i_vizinha, j_vizinha;

    // 1. acima
    i_vizinha = i - 1;
    j_vizinha = j;
    if (i_vizinha == -1) i_vizinha = n_linhas - 1;
    if (matriz[i_vizinha][j_vizinha] == VIVA)
        n_celulas_vivas++;
        
    // 2. à esquerda
    i_vizinha = i;
    j_vizinha = j - 1;
    if (j_vizinha == -1) j_vizinha = n_colunas - 1;
    if (matriz[i_vizinha][j_vizinha] == VIVA)
        n_celulas_vivas++;

    // 3. à direita
    j_vizinha = j + 1;
    if (j_vizinha == n_colunas) j_vizinha = 0;
    if (matriz[i_vizinha][j_vizinha] == VIVA)
        n_celulas_vivas++;

    // 4. abaixo
    i_vizinha = i + 1;
    j_vizinha = j;
    if (i_vizinha == n_linhas) i_vizinha = 0;
    if (matriz[i_vizinha][j_vizinha] == VIVA)
        n_celulas_vivas++;

    if (vizinhanca == MOORE)
    {
        // 5. acima, à esquerda
        i_vizinha = i - 1;
        j_vizinha = j - 1;
        if (i_vizinha == -1) i_vizinha = n_linhas - 1;
        if (j_vizinha == -1) j_vizinha = n_colunas - 1;
        if (matriz[i_vizinha][j_vizinha] == VIVA)
            n_celulas_vivas++;
        
        // 6. acima, à direita
        j_vizinha = j + 1;
        if (j_vizinha == n_colunas) j_vizinha = 0;
        if (matriz[i_vizinha][j_vizinha] == VIVA)
            n_celulas_vivas++;

        // 7. abaixo, à esquerda
        i_vizinha = i + 1;
        j_vizinha = j - 1;
        if (i_vizinha == n_linhas) i_vizinha = 0;
        if (j_vizinha == -1)       j_vizinha = n_colunas - 1;
        if (matriz[i_vizinha][j_vizinha] == VIVA)
            n_celulas_vivas++;

        // 8. abaixo, à direita
        j_vizinha = j + 1;
        if (j_vizinha == n_colunas) j_vizinha = 0;
        if (matriz[i_vizinha][j_vizinha] == VIVA)
            n_celulas_vivas++;
    }
    else if (vizinhanca == VON_NEUMANN)
    {
        // 5. dois acima
        i_vizinha = i - 2;
        j_vizinha = j;
        if (i_vizinha < 0) i_vizinha += n_linhas; 
        if (matriz[i_vizinha][j_vizinha] == VIVA)
            n_celulas_vivas++;

        // 6. dois à esquerda
        i_vizinha = i;
        j_vizinha = j - 2;
        if (j_vizinha < 0) j_vizinha += n_colunas;
        if (matriz[i_vizinha][j_vizinha] == VIVA)
            n_celulas_vivas++;

        // 7. dois à direita
        j_vizinha = j + 2;
        if (j_vizinha >= n_colunas) j_vizinha -= n_colunas;
        if (matriz[i_vizinha][j_vizinha] == VIVA)
            n_celulas_vivas++;

        // 8. dois abaixo
        i_vizinha = i + 2;
        j_vizinha = j;
        if (i_vizinha >= n_linhas) i_vizinha -= n_linhas;
        if (matriz[i_vizinha][j_vizinha] == VIVA)
            n_celulas_vivas++;
    }

    return n_celulas_vivas;
}

void processar_geracao(char **matriz, int n_linhas, int n_colunas, char vizinhanca)
{
    // Alocar memória para uma cópia temporária da matriz:
    char **copia = (char **) malloc(n_linhas * sizeof(char *));
    for (int i = 0; i < n_linhas; i++)
        copia[i] = (char *) malloc(n_colunas * sizeof(char));
    
    // Copiar cada elemento:
    for (int i = 0; i < n_linhas; i++)
    {
        for (int j = 0; j < n_colunas; j++)
            copia[i][j] = matriz[i][j];
    }

    // Processar cada célula:
    for (int i = 0; i < n_linhas; i++)
    {
        for (int j = 0; j < n_colunas; j++)
        {
            int n_vizinhos_vivos = contar_vizinhos_vivos(copia, n_linhas, n_colunas, vizinhanca, i, j);

            if (matriz[i][j] == VIVA && (n_vizinhos_vivos < 2 || n_vizinhos_vivos > 3))
                    matriz[i][j] = MORTA;
            else if (matriz[i][j] == MORTA && n_vizinhos_vivos == 3)
                    matriz[i][j] = VIVA;
        }
    }

    limpar_matriz(copia, n_linhas);
}

int main()
{
    // ENTRADA: dimensões do tabuleiro
    int n_linhas, n_colunas;
    scanf("%d %d", &n_linhas, &n_colunas);
    if (n_linhas <= 0 || n_colunas <= 0)
        erro();
    
    // ENTRADA: número de gerações
    int n_geracoes;
    scanf(" %d", &n_geracoes);
    if (n_geracoes <= 0)
        erro();
    
    // ENTRADA: modelo de vizinhança adotado
    char vizinhanca;
    scanf("%*[\n]s");
    scanf("%c", &vizinhanca);
    scanf("%*[\n]s");
    if (vizinhanca != MOORE && vizinhanca != VON_NEUMANN)
        erro();

    // ENTRADA: configuração da primeira geração
    char **tabuleiro = ler_matriz(n_linhas, n_colunas);

    // Processar n_geracoes gerações:
    for (int i = 0; i < n_geracoes; i++)
        processar_geracao(tabuleiro, n_linhas, n_colunas, vizinhanca);
    
    // SAÍDA: imprimir configuração final
    for (int i = 0; i < n_linhas; i++)
    {
        for (int j = 0; j < n_colunas; j++)
            printf("%c", tabuleiro[i][j]);
        printf("\n");
    }

    // Limpar tabuleiro:
    limpar_matriz(tabuleiro, n_linhas);

    return 0;
}