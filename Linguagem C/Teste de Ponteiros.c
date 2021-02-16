// Ponteiros armazenam endereços de memória de outras variáveis

#include <stdio.h>
#include <stdlib.h>

int main()
{
	//	Declaração de variável e ponteiro
	int ano, *pAno;

	//	Inicialização
	ano = 2020;
	pAno = &ano; //	Referência à 'ano'


	printf("%d \n", ano);
	//	O valor decimal de 'ano'

	printf("%d \n", *&ano);
	//	O valor decimal de 'ano' referenciado pelo seu próprio endereço



	printf("%p \n", &ano);
	//	O endereço de 'ano'


	printf("%d \n", *pAno);
	//	O valor decimal de 'ano' referenciado pelo seu endereço armazenado em 'pAno'



	printf("%p \n", pAno);
	//	O endereço de 'ano' armazenado pelo ponteiro 'pAno'

	printf("%p \n", &pAno);
	//	O endereço do ponteiro 'pAno'

	return 0;
}