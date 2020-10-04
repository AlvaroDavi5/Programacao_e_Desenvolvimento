/*

Calcular area de um circulo maior contendo circulo menor

Alvaro Davi, Eng Comp UFES, 2020

*/

#include <stdio.h>

int main()
{
    float raioMenor, raioMaior, areaMenor, areaMaior, areaDeSobra;
    float const pi = 3.141529;

    scanf("%.6f", &raioMenor);

    raioMaior = (3.0 * raioMenor) / 2.0;  /* diametroMaior = 3 raioMenor */

    areaMenor = pi*(raioMenor*raioMenor);
    areaMaior = pi*(raioMaior*raioMaior);

    areaDeSobra = areaMaior - areaMenor;

    printf("%.4f", areaDeSobra);

    return 0;
}