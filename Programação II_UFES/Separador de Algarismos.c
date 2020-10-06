// 104 % 10 == 14

#include <stdio.h>
#include <math.h>

int main()
{
	int num, potDez, resPot, result, cont;
	int *numCas[10];

	scanf("%i %i", &num, &cont);

	for(int i=0; 1 ;i++)
	{
		while (1) // POTENCIA DE DEZ
		{
			if(i == 0)
			{
				potDez = 1;
				break;
			}
			else if(i == 1)
			{
				potDez = 10;
				break;
			}
			else
			{
				potDez *= 10;
				break;
			}
			//potDez = pow(10, i);
		}

		if((num / potDez) != 0)
		{
			resPot = (num / potDez) * potDez;
			result = resPot;
			numCas[i] = &result;
			printf("%d \n", *numCas[i]);
		}

		if(!(num / potDez))
		{
			break;
		}
	}

	return 0;
}
