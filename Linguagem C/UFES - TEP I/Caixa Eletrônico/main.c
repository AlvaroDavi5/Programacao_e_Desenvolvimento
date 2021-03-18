#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "caixa.h"


int main()
{
	srand(time(NULL));

	char *nome = NULL, *cpf = NULL;

	nome = (char *) malloc(30 * sizeof(char));
	cpf = (char *) malloc(11 * sizeof(char));

	printf("Digite NOME e CPF: ");
	scanf("%[A-Z, a-z] %[0-9]", nome, cpf);

	Conta *user1 = gerarConta(nome, cpf);
	operacao(user1);
	deletarConta(user1);

	free(nome);
	free(cpf);
	cpf = NULL;
	nome = NULL;

	return 0;
}
