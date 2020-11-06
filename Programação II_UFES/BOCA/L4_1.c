/*

Ler numero N de produtos e retornar produtos:
	em FALTA (em ordem de ocorrencia)
	de MAIOR preço (em ordem de ocorrencia, caso empate entre produtos)
	de MENOR preço (em ordem de ocorrencia, caso empate entre produtos)
Os produtos serão dados por seus códigos, preços e quantidade em estoque

Alvaro Davi, Eng Comp UFES, 2020

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int COD;
	float PRE;
	int QTD;
} tProduto;

tProduto LeProduto();
int EhProduto1MaiorQ2(tProduto p1, tProduto p2);
int EhProduto1MenorQ2(tProduto p1, tProduto p2);
int TemProdutoEmEstoque(tProduto p);
void ImprimeProduto(tProduto p);

int main()
{
	int n;
	tProduto pTemp, pMax, pMin;

	scanf("%d", &n);

	if (n > 0)
	{
		for (int i = 0; i < n; i++)
		{
			pTemp = LeProduto();

			if (i == 0)
			{
				pMax = pTemp;
				pMin = pTemp;
			}

			// FALTA
			if (TemProdutoEmEstoque(pTemp))
			{
				// MAIOR
				if (EhProduto1MaiorQ2(pMax, pTemp))
				{
					pMax = pTemp;
				}

				// MENOR
				if (EhProduto1MenorQ2(pMin, pTemp))
				{
					pMin = pTemp;
				}
			}
			else
			{
				printf("FALTA:");
				ImprimeProduto(pTemp);

				// MAIOR
				if (EhProduto1MaiorQ2(pMax, pTemp))
				{
					pMax = pTemp;
				}

				// MENOR
				if (EhProduto1MenorQ2(pMin, pTemp))
				{
					pMin = pTemp;
				}
			}
		}

		// MAIOR
		printf("MAIOR:");
		ImprimeProduto(pMax);	

		// MENOR
		printf("MENOR:");
		ImprimeProduto(pMin);	
	}

	return 0;
}

tProduto LeProduto()
{
	int codigo, quantidade;
	float preco;
	tProduto prod;

	scanf("%d;%f;%d", &codigo, &preco, &quantidade);

	prod.COD = codigo;
	prod.PRE = preco;
	prod.QTD = quantidade;

	return prod;
}

int EhProduto1MaiorQ2(tProduto p1, tProduto p2)
{
	if (p1.PRE >= p2.PRE)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int EhProduto1MenorQ2(tProduto p1, tProduto p2)
{
	if (p1.PRE <= p2.PRE)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int TemProdutoEmEstoque(tProduto p)
{
	if (p.QTD != 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void ImprimeProduto(tProduto p)
{
	printf("COD ");
	printf("%d, ", p.COD);
	printf("PRE ");
	printf("%.2f, ", p.PRE);
	printf("QTD ");
	printf("%d\n", p.QTD);

	return;
}