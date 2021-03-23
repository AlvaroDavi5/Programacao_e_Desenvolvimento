#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuario.h"


struct usr
{
	char *nome;
	long int cpf;
};


Usuario * criarUsuario()
{
	char *nome = NULL;
	long int cpf = 0;
	Usuario *user = NULL;

	user =  (Usuario *) malloc(sizeof(Usuario));
	nome = (char *) malloc(35 * sizeof(char));

	printf("Digite NOME e CPF: ");
	scanf("%[A-Z, a-z] %ld", nome, &cpf);

	user->nome = strdup(nome);
	user->cpf = cpf;

	free(nome);
	nome = NULL;

	return user;
}

char * obterNomeUsuario(Usuario *user)
{
	return user->nome;
}

long int obterCpfUsuario(Usuario *user)
{
	return user->cpf;
}

void deletarUsuario(Usuario *user)
{
	if (user != NULL)
	{
		if (user->nome != NULL)
			free(user->nome);

		free(user);
		user = NULL;
	}
}

