#ifndef _CONTA_H_

	#define _CONTA_H_

	#include "usuario.h"

	typedef struct acc Conta;

	Conta * gerarConta(Usuario *user);
	void operacao(Conta *account);
	float depositar(float saldo, float valor);
	float sacar(float saldo, float valor);
	void infoConta(Conta *account);
	void deletarConta(Conta *account);

#endif
