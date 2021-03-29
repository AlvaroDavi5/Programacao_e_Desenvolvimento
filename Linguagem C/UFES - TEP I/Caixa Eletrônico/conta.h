#ifndef _CONTA_H_

	#define _CONTA_H_

	#include "usuario.h"

	typedef struct acc Conta;

	Conta * gerarConta(Usuario *user);
	void deletarConta(Conta *account);
	void operacao(Conta **accounts, int qtdAcc);
	void depositar(Conta *account, float valor);
	int sacar(Conta *account, float valor);
	int transferir(Conta *contaOrig, Conta *contaDest, float valor);
	Conta * buscarConta(Conta **accounts, int qtdAcc, int nConta);
	Usuario * obterUsuario(Conta *account);
	int obterAgencia(Conta *account);
	int obterConta(Conta *account);
	float obterSaldo(Conta *account);
	void infoConta(Conta *account);
	void infoTodasContas(Conta** contas, int qtdAcc);
	void deletarTodasContas(Conta** contas, int qtdAcc);

#endif
