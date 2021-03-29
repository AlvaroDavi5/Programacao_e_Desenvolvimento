#include <stdio.h>
#include <stdlib.h>
#include "conta.h"


struct acc
{
	Usuario *usuario;
	int agencia; // optei por manter a agência
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

void operacao(Conta **accounts, int qtdAcc)
{
	int op = 999, numConta1 = 0, numConta2 = 0;
	long int cpf = 0;
	char *nome = NULL;
	float valor = 0.00;
	Usuario *usuario;
	Conta *conta1 = NULL, *conta2 = NULL;

	nome = (char *) malloc(45 * sizeof(char));

	do
	{
		printf("\nEscolha uma operação (0-sair; 1-saque; 2-depósito; 3-transferência; 4-criar conta; 5-relatório): ");
		scanf("%d", &op);

		switch(op)
		{
			case 0:
				printf("SAINDO...\n \n");
				exit(0);
				break;

			case 1:
				printf("\nDigite o número da conta e o valor de saque: ");
				scanf("%d %f", &numConta1, &valor);
				conta1 = buscarConta(accounts, qtdAcc, numConta1);
				if (conta1)
					sacar(conta1, valor);
				else
					printf("Conta inexistente!\n");
				break;

			case 2:
				printf("\nDigite o número da conta e o valor de depósito: ");
				scanf("%d %f", &numConta1, &valor);
				conta1 = buscarConta(accounts, qtdAcc, numConta1);
				if (conta1)
					depositar(conta1, valor);
				else
					printf("Conta inexistente!\n");
				break;

			case 3:
				printf("\nDigite o número das contas (origem >> destino) e o valor da transferência: ");
				scanf("%d %d %f", &numConta1, &numConta2, &valor);
				conta1 = buscarConta(accounts, qtdAcc, numConta1);
				conta2 = buscarConta(accounts, qtdAcc, numConta2);
				if (conta1 && conta2)
					transferir(conta1, conta2, valor);
				else
					printf("Uma das contas não existem!\n");
				break;

			case 4:
				qtdAcc++;
				accounts = (Conta **) realloc(accounts, qtdAcc * sizeof(Conta *));
				printf("Digite NOME e CPF: ");
				scanf("%[^0-9] %ld", nome, &cpf);
				usuario = criarUsuario(nome, cpf);
				free(nome);
				nome = NULL;
				accounts[qtdAcc - 1] = gerarConta(usuario);
				break;

			case 5:
				printf("\n ----------------------- RELATÓRIO ----------------------- \n");
				infoTodasContas(accounts, qtdAcc);
				printf("\n");
				break;

			default:
				printf("\nOperação inválida!\n");
				break;
		}

		valor = 0.00;
		numConta1 = 0;
		numConta2 = 0;
	} while (op != 0);
}

void depositar(Conta *account, float valor)
{
	printf("DEPOSITANDO...\n");
	account->saldo += valor;
}

int sacar(Conta *account, float valor)
{
	if (account->saldo >= valor)
	{
		account->saldo -= valor;
		printf("SACANDO/TRANSFERINDO...\n");
		return 1;
	}
	else
	{
		printf("Valor excede o saldo atual!\n");
		return 0;
	}
}

int transferir(Conta *contaOrig, Conta *contaDest, float valor)
{
	if (sacar(contaOrig, valor))
	{
		depositar(contaDest, valor);
		return 1;
	}
	else
		return 0;
}

Conta * buscarConta(Conta **accounts, int qtdAcc, int nConta)
{
	for (int i = 0; i < qtdAcc; i++)
	{
		if (accounts[i]->conta == nConta)
			return accounts[i];
	}

	return NULL;
}

void infoConta(Conta *account)
{
	printf("Usuário: %s \n", obterNomeUsuario(account->usuario));
	printf("CPF: %06ld \n", obterCpfUsuario(account->usuario));
	printf("Conta: %d \n", account->conta);
	printf("Agência: %d \n", account->agencia);
	printf("Saldo: %.2f \n", account->saldo);
}

void infoTodasContas(Conta** accounts, int qtdAcc)
{
	for (int i = 0; i < qtdAcc; i++)
	{
		infoConta(accounts[i]);
		printf("\n");
	}
}

void deletarTodasContas(Conta** accounts, int qtdAcc)
{
	for (int i = 0; i < qtdAcc; i++)
	{
		deletarConta(accounts[i]);
	}
}

Usuario * obterUsuario(Conta *account)
{
	return account->usuario;
}

int obterAgencia(Conta *account)
{
	return account->agencia;
}

int obterConta(Conta *account)
{
	return account->conta;
}

float obterSaldo(Conta *account)
{
	return account->saldo;
}
