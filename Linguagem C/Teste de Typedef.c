#include <stdio.h>
#include <math.h>

typedef float real; // atribui o nome 'real' para o tipo float (em escopo global)

int main()
{
	real num;

	scanf("%f", &num);
	printf("%.4f", num);

	return 0;
}