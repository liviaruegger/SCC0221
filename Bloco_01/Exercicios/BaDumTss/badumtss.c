#include <stdio.h>
#include <stdbool.h>

int main()
{
    int n;
    
    float q1, q2, q3;
    
    /* Apesar de serem inteiros, precisamos declarar n1, n2 e n3 como float.
    Se forem declarados como inteiros, os quocientes q1, q2 e q3 serão sempre
    registrados como inteiros (divisão de int por int). */
    float n1 = 11;
    float n2 = 13;
    float n3 = 19;    
    
    bool ba = false; 
    bool dum = false;
    bool tss = false;

    scanf("%i", &n);

    q1 = n/n1;
    q2 = n/n2;
    q3 = n/n3;

    /* Para verificar se uma variável é um número é inteiro, podemos simplemesnte
    compará-la com o número que resulta quando modificamos seu tipo de dado para
    inteiro (type casting): if (numero == (int)numero) */
    
    if (q1 == (int)q1) // n é divisível por 11 (ba)
        ba = true;

    if (q2 == (int)q2) // n é divisível por 13 (dum)
        dum = true;

    if (q3 == (int)q3) // n é divisível por 19 (tss)
        tss = true;  

    // DIVISÍVEL PELOS 3 NÚMEROS
    // BaDumTssTss -> ba, dum, tss
    if (ba == true && dum == true && tss == true)
        printf("BaDumTssTss");
    
    // DIVISÍVEL POR 2 DOS NÚMEROS
    // BaDumDum -> ba, dum
    else if (ba == true && dum == true)
        printf("BaDumDum");
    // BaDumTss -> ba, tss
    else if (ba == true && tss == true)
        printf("BaDumTss");
    // DumDumTss -> dum, tss
    else if (dum == true && tss == true)
        printf("DumDumTss");

    // DIVISÍVEL POR APENAS 1 NÚMERO
    // BaBa -> ba
    else if (ba == true)
        printf("BaBa");
    // BaDum -> dum
    else if (dum == true)
        printf("BaDum");
    // BaTss -> tss
    else if (tss == true)
        printf("BaTss");
    
    // NÃO É DIVISÍVEL POR NENHUM DOS NÚMEROS
    // Imprime o próprio n
    else
        printf("%i", n);

    return 0;
}