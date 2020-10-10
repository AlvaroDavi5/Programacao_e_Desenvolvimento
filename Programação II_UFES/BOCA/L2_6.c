/*

Calcular somatorio de (i / k)

Alvaro Davi, Eng Comp UFES, 2020

*/

#include <stdio.h>
#include <math.h>

int main()
{
	int sit, expo;
	int i = 1, k = 1;
	float result;

	scanf("%d", &sit);

	switch (sit)
	{
	case 1:
		while (k < 51)
		{
			result += (i / k);
			k++;
			i += 2;
		}
		break;
	case 2:
		//
		break;
	case 3:
		//
		break;
	default:
		break;
	}

	printf("%.6f", result);

	return 0;
}