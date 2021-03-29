#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuario.h"


struct usr
{
	char *nome;
	long int cpf;
};


Usuario * criarUsuario(char *nome, long int cpf)
{
	Usuario *user = NULL;

	user =  (Usuario *) malloc(sizeof(Usuario));

	user->nome = strdup(nome);
	user->cpf = cpf;

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
		{
			free(user->nome);
			user->nome = NULL;
		}

		free(user);
		user = NULL;
	}
}
