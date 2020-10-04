/*
ler CO e CA
Hip = raizq(CO² + CA²)
mostrar Hip
*/

#include <stdio.h>
#include <math.h>

float main()
{
    int CA, CO;
    float Hip;

    printf("Digite o valor do cateto oposto:");
    scanf("%d", &CO);
    printf("Digite o valor do cateto adjacente:");
    scanf("%d", &CA);
    Hip = sqrt((CO*CO)+(CA*CA));
    printf("O valor da hipotenusa é: %f \n",Hip);
    return 0;
}