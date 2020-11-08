#include <stdio.h>
#include <stdlib.h>

int main()
{
	int numbs[10]  = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // array com 10 espaços

	printf("VETOR: ");
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", numbs[i]);
	}
	printf("\n");

	return 0;
}