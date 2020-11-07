/*

	FORMATO

 1

      1
    2 1 2
  3 2 1 2 3
    2 1 2
      1

*/

#include <stdio.h>
#include <stdlib.h>

void printNumber(int num);
void printNumberInv(int num);
void printTopo(int n);
void printBase(int n);
void printSpace(int num);
void printFinal(int n);

int main()
{
	int n;

	scanf("%d", &n);
	printFinal(n);

	return 0;
}


void printNumber(int num)
{
	int i;

	for (i = 1; i < num; i++)
	{
		printf("%d ", i);
	}
	printf("%d", i);

	return;
}

void printNumberInv(int num)
{
	int i;

	for (i = num; i > 1; i--)
	{
		printf("%d ", i);
	}

	return;
}

void printTopo(int n)
{
	int i, j, k = n;

	for (i = 1; i <= n; i++)
	{
		printSpace(k);
		printNumberInv(n);
		printNumber(n);
		printf("\n");
		k--;
	}
}

void printBase(int n)
{
	int i, j, k = 2;

	for (i = n-1; i >= 1; i--)
	{
		printSpace(k);
		printNumberInv(n);
		printNumber(n);
		printf("\n");
		k++;
	}
}

void printSpace(int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		printf(" ");
	}
}

void printFinal(int n)
{
	printTopo(n);
	printBase(n);
}