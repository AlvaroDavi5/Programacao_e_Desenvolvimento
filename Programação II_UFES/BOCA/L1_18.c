/*

Verificar quadrante de um ponto

Alvaro Davi, Eng Comp UFES, 2020

*/

#include <stdio.h>

int main()
{
	float x, y;
	int quad;

	scanf("%f %f", &x, &y);

	/* QUADRANTES: 1 = (++), 2 = (-+), 3 = (--), 4 = (+-) */

	if(x > 0) // eixoX: +
	{
		if(y > 0) // eixoY: +
		{
			quad = 1;
		}
		if(y < 0) // eixoY: -
		{
			quad = 4;
		}
		if(y == 0) // eixoY: 0
		{
			quad = 0;
		}
	}

	if(x < 0) // eixoX: -
	{
		if(y > 0) // eixoY: +
		{
			quad = 2;
		}
		if(y < 0) // eixoY: -
		{
			quad = 3;
		}
		if(y == 0) // eixoY: 0
		{
			quad = 0;
		}
	}

	if(x == 0) // eixoX: 0
	{
		quad = 0;
	}

	if(quad != 0)
	{
		printf("%i", quad);
	}
	if(quad == 0)
	{
		printf("ORIGEM");
	}

	return 0;
}