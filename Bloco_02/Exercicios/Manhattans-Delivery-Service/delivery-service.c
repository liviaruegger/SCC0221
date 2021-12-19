#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define VALOR_INVALIDO 2

#define BALDIO -1
#define RESIDENCIAL 0
#define PARQUE 1

float diagonal(int x_inicial, int y_inicial, int x_final, int y_final)
{
    float distancia_percorrida = sqrt(pow((x_final - x_inicial), 2) + pow((y_final - y_inicial), 2));
    return distancia_percorrida;
}

int calcadas(int x_inicial, int y_inicial, int x_final, int y_final)
{
    float distancia_percorrida = abs(x_final - x_inicial) + abs(y_final - y_inicial);
    return distancia_percorrida;
}

float dist_euclides(int x_inicial, int y_inicial, int x_final, int y_final, int terreno)
{
    float distancia_percorrida;
    if (terreno == RESIDENCIAL)
        distancia_percorrida = calcadas(x_inicial, y_inicial, x_final, y_final);
    else
        distancia_percorrida = diagonal(x_inicial, y_inicial, x_final, y_final);
    return distancia_percorrida;
}

float dist_hermann(int x_inicial, int y_inicial, int x_final, int y_final, int terreno)
{
    float distancia_percorrida;
    if (terreno == BALDIO)
        distancia_percorrida = diagonal(x_inicial, y_inicial, x_final, y_final);
    else
        distancia_percorrida = calcadas(x_inicial, y_inicial, x_final, y_final);
    return distancia_percorrida;
}

void erro()
{
    printf("Falha no processamento dos dados.\n");
    exit(0);
}

int main()
{   
    int n;
    scanf(" %d", &n);

    if (n < 1) erro();

    int x_casa, y_casa, terreno;
    scanf(" %d %d %d", &x_casa, &y_casa, &terreno);

    int x_inicial = x_casa;
    int y_inicial = y_casa;
    int x_final, y_final;

    float total_euclides = 0;
    float total_hermann = 0;

    int cont_baldio = 0;
    int cont_residencial = 0;
    int cont_parque = 0;

    if (terreno == BALDIO) cont_baldio++;
    else if (terreno == RESIDENCIAL) cont_residencial++;
    else if (terreno == PARQUE) cont_parque++;

    for (int i = 1; i < n; i++)
    {   
        int prox_terreno = VALOR_INVALIDO;
        scanf("%d %d %d\n", &x_final, &y_final, &prox_terreno);

        if (prox_terreno == VALOR_INVALIDO) erro();

        total_euclides += dist_euclides(x_inicial, y_inicial, x_final, y_final, terreno);
        total_hermann += dist_hermann(x_inicial, y_inicial, x_final, y_final, terreno);

        terreno = prox_terreno;

        if (terreno == BALDIO) cont_baldio++;
        else if (terreno == RESIDENCIAL) cont_residencial++;
        else if (terreno == PARQUE) cont_parque++;

        x_inicial = x_final;
        y_inicial = y_final;
    }

    total_euclides += dist_euclides(x_inicial, y_inicial, x_casa, y_casa, terreno);
    total_hermann += dist_hermann(x_inicial, y_inicial, x_casa, y_casa, terreno);

    printf("Ao todo, foi passado por %d terrenos baldios, %d terrenos residenciais e %d parques.\n", cont_baldio, cont_residencial, cont_parque);
    printf("A diferenca total de distancia percorrida foi de %.2f metros.\n", total_hermann - total_euclides);
    
    return 0;
}