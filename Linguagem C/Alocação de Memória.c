#include <stdio.h>

void mudaEndereco(int *ref);

int main()
{
	int num = 12, *ptr;

	ptr = &num;

	printf("Endereco inicial: %p \n", ptr);

	mudaEndereco(&num);

	printf("Endereco final: %p \n", ptr);

	return 0;
}


void mudaEndereco(int *ref)
{
	int *ptr;

	ptr = ref;
	printf("Endereco intermediario: %p \n", ptr);
}
