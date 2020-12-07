#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

void verificarSeMatrizDiagonal(int matriz[100][100], int ordemMatriz);

int main()
{
	int ordemMatriz;

	scanf("%d%*c%*c", &ordemMatriz); // ler ordem (M linhas e N colunas) da matriz quadrada (M == N, NxN)

	int matriz[ordemMatriz][ordemMatriz]; // definir dimensoes da matriz

	scanf("%*c");
	for (int i = 0; i < ordemMatriz; i++) // para acessar linhas
	{
		scanf("%*c");
		for (int j = 0; j < ordemMatriz; j++) // para preencher colunas
		{
			scanf("%d%*c", &matriz[i][j]);
		}
		scanf("%*c");
	}
	scanf("%*c");

	verificarSeMatrizDiagonal(matriz, ordemMatriz);

	for (int k = 0; k < ordemMatriz; k++)
	{
		for (int l = 0; l < ordemMatriz; l++)
		{
			printf("%d ", matriz[k][l]);
		}
		printf("\n");
	}

	return 0;
}


void verificarSeMatrizDiagonal(int matriz[100][100], int ordemMatriz)
{
	int verif = FALSE, logic = TRUE;

	for (int i = 0; i < (ordemMatriz - 1) && logic; i++) // varrer linhas
	{
		for (int j = 0; j < (ordemMatriz - 1) && logic; j++) // varrer colunas
		{
			if (matriz[i][j] == matriz[i+1][j+1])
			{
				verif = TRUE;
			}
			else
			{
				verif = FALSE;
				logic = FALSE;
				break;
			}
		}
	}


	if (verif != FALSE)
	{
		printf("SIM");
	}
	else
	{
		printf("NAO");
	}
}