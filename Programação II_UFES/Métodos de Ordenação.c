// bubblesortOrdenation (correto)
// insertionsortOrdenation (repetindo valores)
// quicksortOrdenation (adcionando 0 e removendo ultimo valor)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define ARRAYSIZE 15

void bubbleSort(int array[]);
void insertionSort(int array[]);
void quickSort(int array[], int begin, int end);
int partitions(int array[], int begin, int end);
void randomValues(int array[]);
void printArray(int array[]);

int main()
{
	int array1[ARRAYSIZE], array2[ARRAYSIZE], array3[ARRAYSIZE];

	// preencher aleatoriamente vetores
	printf("VETOR 1: ");
	randomValues(array1);
	printf("VETOR 2: ");
	randomValues(array2);
	printf("VETOR 3: ");
	randomValues(array3);

	printf("\n");

	// ordenar de formas diferentes
	printf("bubbleSort V1: ");
	bubbleSort(array1);
	printArray(array1);
	printf("insertionSort V2: ");
	insertionSort(array2);
	printArray(array2);
	printf("quickSort V3: ");
	quickSort(array3, 0, ARRAYSIZE);
	printArray(array3);

	return 0;
}



void randomValues(int array[])
{
	srand(time(NULL));
	for (int i = 0; i < ARRAYSIZE; i++)
	{
		const random = rand() % 50;
		array[i] = random;
	}

	printArray(array);
}



void bubbleSort(int array[])
{
	int memory, shift = TRUE, i, j;

	for (j = (ARRAYSIZE - 1); (j >= 1) && (shift); j--)
	{
		shift = FALSE; // se o valor continuar 'false' na proxima iteracao entao nao houve troca e a funcao termina
		
		for (i = 0; i < j; i++)
		{
			if (array[i] > array[i+1]) // se o valor da posicao i for maior que o valor da posicao i+1
			{
				memory = array[i]; // salva temporariamente o valor da posicao i
				array[i] = array[i+1]; // coloca o valor da posicao i+1 na posicao i
				array[i+1] = memory; // coloca o valor salvo temporariamente na posicao i+1
				shift = TRUE; // sinalizada a troca para manter o loop
			}
		}
	}
}



void insertionSort(int array[])
{
	int i, count, memory, mark;

	for (i = 1; i < ARRAYSIZE; i++)
	{
		memory = array[i];
		count = i-1;

		do
		{
			mark = FALSE;
			if (array[count] > memory)
			{
				array[count+1] = array[count];
				count--;
				mark = TRUE;
			}
			if (count < 0)
			{
				mark = FALSE;
			}
		} while (mark);
	}
	array[count+1] = memory;
}



void quickSort(int array[], int begin, int end)
{
	int pivot;

	if (end > begin)
	{
		pivot = partitions(array, begin, end); // particiona o vetor e escolhe pivo
		quickSort(array, begin, pivot-1); // ordena as 2 particoes
		quickSort(array, pivot+1, end);
	}
}

int partitions(int array[], int begin, int end)
{
	int left, right, pivot, aux;

	left = begin; // esquerda recebe o inicio e direita, o final
	right = end;
	pivot = array[begin]; // pivo e a primeira posicao do vetor

	while (left < right)
	{
		while (array[left] <= pivot)
		{
			left++; // avanca posicao da esquerda
		}
		while (array[right] > pivot)
		{
			right--; // recua posicao da direita
		}

		if (left < right)
		{
			aux = array[left]; // trocar valores com variavel temporaria
			array[left] = array[right];
			array[right] = aux;
		}
	}
	array[begin] = array[right];
	array[right] = pivot;

	return right;
}



void printArray(int array[])
{
	for (int i = 0; i < ARRAYSIZE; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
}