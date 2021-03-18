#ifndef _CAIXA_H_

	#define _CAIXA_H_

	typedef struct
	{
		char *nome;
		char *cpf;
	} Usuario;

	typedef struct
	{
		Usuario pessoal;
		int agencia;
		int conta;
		float saldo;
	} Conta;

	Conta * gerarConta(char *nome, char *cpf);
	void operacao(Conta *account);
	void depositar(Conta *account, float valor);
	void sacar(Conta *account, float valor);
	void infoConta(Conta *account);
	void * deletarConta(Conta *usr);

#endif
