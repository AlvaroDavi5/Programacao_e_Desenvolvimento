#ifndef _USUARIO_H_

	#define _USUARIO_H_

	typedef struct usr Usuario;

	Usuario * criarUsuario(char *nome, long int cpf);
	char * obterNomeUsuario(Usuario *user);
	long int obterCpfUsuario(Usuario *user);
	void deletarUsuario(Usuario *user);

#endif
