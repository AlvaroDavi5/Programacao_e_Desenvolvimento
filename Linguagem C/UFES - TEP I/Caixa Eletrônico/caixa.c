#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "caixa.h"


Conta * gerarConta(char *nome, char *cpf)
{
	Conta *usuario;
	usuario = (Conta *) malloc(sizeof(Conta));

	usuario->pessoal.nome = strdup(nome);
	usuario->pessoal.cpf = strdup(cpf);
	usuario->agencia = (rand() % 9999) + 1;
	usuario->conta = (rand() % 99999) + 1;
	usuario->saldo = 0.00;

	return usuario;
}

void operacao(Conta *account)
{
	int op = 999;
	float valor = 0.00;

	do
	{
		//scanf("\nEscolha uma operação (0-sair; 1-saque; 2-depósito): %d \n", &op);
		printf("\nEscolha uma operação (0-sair; 1-saque; 2-depósito): ");
		scanf("%d", &op);

		if (op == 0)
		{
			printf("SAINDO...\n \n");
			break;
		}
		else if (op == 1)
		{
			printf("\nDigite o valor de saque: ");
			scanf("%f", &valor);
			sacar(account, valor);
		}
		else if (op == 2)
		{
			printf("\nDigite o valor de depósito: ");
			scanf("%f", &valor);
			depositar(account, valor);
		}
		else
		{
			printf("\nOperação inválida!\n");
		}

	valor = 0.00;
	} while (op != 0);

	infoConta(account);
}

void depositar(Conta *account, float valor)
{
	printf("DEPOSITANDO...\n");
	account->saldo += valor;
}

void sacar(Conta *account, float valor)
{
	if (account->saldo >= valor)
	{
		account->saldo -= valor;
		printf("SACANDO...\n");
	}
	else
		printf("Valor excede o saldo atual!\n");
}

void infoConta(Conta *account)
{
	printf("Usuário: %s \n", account->pessoal.nome);
	printf("Conta: %d \n", account->conta);
	printf("Agência: %d \n", account->agencia);
	printf("Saldo: %.2f \n", account->saldo);
}

void * deletarConta(Conta *usr)
{
	if (usr != NULL)
	{
		if (usr->pessoal.nome != NULL)
			free(usr->pessoal.nome);

		if (usr->pessoal.cpf != NULL)
			free(usr->pessoal.cpf);

		free(usr);
		usr = NULL;
	}
}
