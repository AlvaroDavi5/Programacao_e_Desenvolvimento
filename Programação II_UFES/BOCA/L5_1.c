/*

Ler N notas e calcular Menor, Maior, Media, Desvio Padrão, quantidade Acima da Media, Quantidade Reprovados

Alvaro Davi, Eng Comp UFES, 2020

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void menorNota(int n, int notasAlunos[]);
void maiorNota(int n, int notasAlunos[]);
float media_artim(int n, int notasAlunos[]);
float desvioPadrao(int n, float media, int notasAlunos[]);
void qtdAcimaMedia(int n, float media, int notasAlunos[]);
void qtdReprovados(int n, int notasAlunos[]);

int main()
{
	int n;

	scanf("%d", &n);

	int notasAlunos[n];

	for (int i = 0; i < n; i++)
	{
		scanf("%d", &notasAlunos[i]);
	}

	menorNota(n, notasAlunos);
	maiorNota(n, notasAlunos);
	
	float media = media_artim(n, notasAlunos);
	printf("MEDIA:%.2f, ", media);
	printf("STD:%.2f, ", desvioPadrao(n, media, notasAlunos));

	qtdAcimaMedia(n, media, notasAlunos);
	qtdReprovados(n, notasAlunos);

	return 0;
}


void menorNota(int n, int notasAlunos[])
{
	int menor = notasAlunos[0];

	for (int i = 0; i < n; i++)
	{
		if (notasAlunos[i] < menor)
		{
			menor = notasAlunos[i];
		}
	}

	printf("MENOR:%d, ", menor);
}

void maiorNota(int n, int notasAlunos[])
{
	int maior = notasAlunos[0];

	for (int i = 0; i < n; i++)
	{
		if (notasAlunos[i] > maior)
		{
			maior = notasAlunos[i];
		}
	}

	printf("MAIOR:%d, ", maior);
}

float media_artim(int n, int notasAlunos[])
{
	float somNotas, med;

	for (int i = 0; i < n; i++)
	{
		somNotas += notasAlunos[i];
	}

	med = (somNotas / (n - 0.00));

	return med;
}

float desvioPadrao(int n, float media, int notasAlunos[])
{
	float somQuadDiffM, DP;

	for (int i = 0; i < n; i++)
	{
		somQuadDiffM += pow((notasAlunos[i] - media), 2);
	}

	DP = sqrt(somQuadDiffM / (n - 0.00)); // sem o -1.00 pois eh desvio padrao populacional (nao amostral)

	return DP;
}

void qtdAcimaMedia(int n, float media, int notasAlunos[])
{
	int qtd = 0;

	for (int i = 0; i < n; i++)
	{
		if (notasAlunos[i] > media)
		{
			qtd++;
		}
	}

	printf("ACIMA_MEDIA_CONC:%d, ", qtd);
}

void qtdReprovados(int n, int notasAlunos[])
{
	int qtd = 0;

	for (int i = 0; i < n; i++)
	{
		if (notasAlunos[i] < 70)
		{
			qtd++;
		}
	}

	printf("REPROV:%d", qtd);
}
