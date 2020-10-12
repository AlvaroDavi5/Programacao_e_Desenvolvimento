#include <stdio.h>
#include <math.h>

int main()
{
	int num, soma = 0;
	int algU, algD, algC, algM;

	scanf("%i", &num);

	algU = (num % 10);
	algD = (num % 100)/10;
	algC = (num % 1000)/100;
	algM = (num % 10000)/1000;

	for (int i =0; i <= num; i++)
	{

		if (num >= 0 && num < 10)
		{
			soma = (algU * algU);
		}

		else if (num >= 10 && num < 100)
		{
			soma = (algU*algU) + (algD*algD);
		}

		else if (num >= 100 && num < 1000)
		{
			soma = (algU*algU) + (algD*algD) + (algC*algC);
		}

		else if (num >= 1000 && num < 10000)
		{
			soma = (algU*algU) + (algD*algD) + (algC*algC) + (algM*algM);
		}

		else /* if (num < 0 || num >= 10000) */
		{
			printf("VALOR DEMASIADO PEQUENO/GRANDE");
		}
	}

	return 0;
}