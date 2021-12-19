#include <stdio.h>

int main()
{
    float tFarenheit; 
    float tCelsius;

    // printf("Digite a temperatura em Farenheit\n");
    scanf("%f", &tFarenheit);

    tCelsius = (tFarenheit - 32)*5/9;

    printf("%.2f\n", tCelsius);

    return 0;
}