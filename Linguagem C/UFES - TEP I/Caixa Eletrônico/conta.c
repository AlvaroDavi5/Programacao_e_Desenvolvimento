#include <stdio.h>
#include <stdlib.h>
#include "conta.h"


struct acc
{
	Usuario *usuario;
	int agencia;
	int conta;
	float saldo;
};


Conta * gerarConta(Usuario *user)
{
	Conta *account = NULL;
	account = (Conta *) malloc(sizeof(Conta));

	account->usuario = user;
	account->agencia = (rand() % 9989) + 10;
	account->conta = (rand() % 99989) + 10;
	account->saldo = 0.00;

	return account;
}

void deletarConta(Conta *account)
{
	if (account != NULL)
	{
		deletarUsuario(account->usuario);

		free(account);
		account = NULL;
	}
}

void operacao(Conta *account)
{
	int op = 999;
	float valor = 0.00;

	do
	{
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
			account->saldo = sacar(account->saldo, valor);
		}
		else if (op == 2)
		{
			printf("\nDigite o valor de depósito: ");
			scanf("%f", &valor);
			account->saldo = depositar(account->saldo, valor);
		}
		else
		{
			printf("\nOperação inválida!\n");
		}

	valor = 0.00;
	} while (op != 0);

	infoConta(account);
}

float depositar(float saldo, float valor)
{
	printf("DEPOSITANDO...\n");
	saldo += valor;
	
	return saldo;
}

float sacar(float saldo, float valor)
{
	if (saldo >= valor)
	{
		saldo -= valor;
		printf("SACANDO...\n");
	}
	else
		printf("Valor excede o saldo atual!\n");

	return saldo;
}

void infoConta(Conta *account)
{
	printf("Usuário: %s \n", obterNomeUsuario(account->usuario));
	printf("CPF: %06ld \n", obterCpfUsuario(account->usuario));
	printf("Conta: %d \n", account->conta);
	printf("Agência: %d \n", account->agencia);
	printf("Saldo: %.2f \n", account->saldo);
}

