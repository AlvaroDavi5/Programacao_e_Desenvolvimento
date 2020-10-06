#include <stdio.h>
#include <math.h>

int main()
{
	int num, id;
	int algU, algD, algC, algM;

	scanf("%d %i", &num, &id);

	algU = (num % 10);
	algD = (num % 100)/10;
	algC = (num % 1000)/100;
	algM = (num % 10000)/1000;

	// UNIDADES
	if (num < 10 && id == 0) // para obter VOID
	{
		printf("VOID");
	}
	else if (num < 10 && id >= 1) // para obter Unidade
	{
		printf("%d", algU);
	}

	// DEZENAS
	else if (num < 100 && id == 0) // para obter Dezena
	{
		printf("%d", algD);
	}
	else if (num < 100 && id == 1) // para obter Unidade
	{
		printf("%d", algU);
	}
	else if (num < 100 && id >= 2) // para comparar Unidade X Dezena
	{
		if (algU >= algD)
		{
			printf("%d, %d", algD, algU);
		}
		if (algU < algD)
		{
			printf("%d, %d", algU, algD);
		}
	}

	// CENTENAS
	else if (num < 1000 && id == 0) // para comparar Denzena X Centena
	{
		if (algD >= algC)
		{
			printf("%d, %d", algC, algD);
		}
		if (algD < algC)
		{
			printf("%d, %d", algD, algC);
		}
	}
	else if (num < 1000 && id == 1) // para comparar Unidade X Centena
	{
		if (algU >= algC)
		{
			printf("%d, %d", algC, algU);
		}
		if (algU < algC)
		{
			printf("%d, %d", algU, algC);
		}
	}
	else if (num < 1000 && id == 2) // para comparar Unidade X Dezena
	{
		if (algU >= algD)
		{
			printf("%d, %d", algD, algU);
		}
		if (algU < algD)
		{
			printf("%d, %d", algU, algD);
		}
	}
	else if (num < 1000 && id >= 3) // para comparar Unidade X Dezena X Centena
	{
		if (algU >= algD)
		{
			if (algD >= algC)
			{
				printf("%d, %d, %d", algC, algD, algU);
			}
			if (algD < algC)
			{
				printf("%d, %d, %d", algD, algC, algU);
			}
		}
		if (algU < algD)
		{
			if (algU >= algC)
			{
				printf("%d, %d, %d", algU, algC, algD);
			}
			if (algU < algC)
			{
				printf("%d, %d, %d", algC, algU, algD);
			}
		}
	}

	// UNIDADES DE MILHAR
	else if (num < 10000 && id == 0) // para comparar Denzena X Centena X Milhar
	{
		if (algD >= algC)
		{
			if (algC >= algM)
			{
				printf("%d, %d, %d", algM, algC, algD);
			}
			if (algC < algM)
			{
				printf("%d, %d, %d", algC, algM, algD);
			}
		} // 																	--------------------------------------------
		if (algD < algC)
		{
			if (algC >= algM)
			{
				printf("%d, %d, %d", algD, algC, algM);
			}
			if (algC < algM)
			{
				printf("%d, %d, %d", algC, algD, algM);
			}
		}
	}
	else if (num < 10000 && id == 1) // para comparar Unidade X Centena X Milhar
	{
		if (algU >= algC)
		{
			if (algC >= algM)
			{
				printf("%d, %d, %d", algM, algC, algU);
			}
			if (algC < algM)
			{
				printf("%d, %d, %d", algC, algM, algU);
			}
		}
		if (algU < algC)
		{
			if (algC >= algM)
			{
				printf("%d, %d, %d", algU, algC, algM);
			}
			if (algC < algM)
			{
				printf("%d, %d, %d", algC, algU, algM);
			}
		}
	}
	else if (num < 10000 && id == 2) // para comparar Unidade X Dezena X Milhar
	{
		if (algU >= algD)
		{
			printf("%d, %d", algD, algU);
		}
		if (algU < algD)
		{
			printf("%d, %d", algU, algD);
		}
	}
	else if (num < 10000 && id >= 3) // para comparar Unidade X Dezena X Centena
	{
		if (algU >= algD)
		{
			if (algD >= algC)
			{
				printf("%d, %d, %d", algC, algD, algU);
			}
			if (algD < algC)
			{
				printf("%d, %d, %d", algD, algC, algU);
			}
		}
		else if (algU < algD)
		{
			if (algU >= algC)
			{
				printf("%d, %d, %d", algU, algC, algD);
			}
			if (algU < algC)
			{
				printf("%d, %d, %d", algC, algU, algD);
			}
		}
	}

	return 0;
}