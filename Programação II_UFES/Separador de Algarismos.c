#include <stdio.h>
#include <math.h>

int main()
{
	int num, potDez;

	scanf("%i", &num);

	for(int i=0; 1 ;i++)
	{
		potDez = pow(10, i);

		if((num / potDez) != 0)
		{
			printf("AA");
		}

		if(!(num / potDez))
		{
			printf("FIM");
			break;
		}
	}

	return 0;
}