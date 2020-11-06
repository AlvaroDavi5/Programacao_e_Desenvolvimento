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

	scanf("%d", &n);

	if (n > 0)
	{
		for (int i = 0; i < n; i++)
		{
			//
		}
	}

	return 0;
}