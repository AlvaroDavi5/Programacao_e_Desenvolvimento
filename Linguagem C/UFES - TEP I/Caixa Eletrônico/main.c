#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "conta.h"


int main()
{
	srand(time(NULL));

	Usuario *user1 = criarUsuario();
	Conta *account_user1 = gerarConta(user1);

	operacao(account_user1);

	deletarConta(account_user1);

	return 0;
}
