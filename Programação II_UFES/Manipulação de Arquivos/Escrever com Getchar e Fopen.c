#include <stdio.h>
#include <stdlib.h>

int main()
{
	char letra, c;

	printf("Digite um texto para ser salvo, finalize com '.' e depois do ponto digite apenas 1 caractere \n");

	FILE *arq; //	ponteiro de arquivo, armazena o endereço das posições do arquivo
	arq = fopen("./arquivo.txt", "a+"); // abrir arquivo (endereço_arquivo, MODO_abertura), função passando por referência

	if (arq == NULL) // caso o arquivo não exista, a função retorna um ponteiro nulo (NULL)
	{
		printf("Erro na abertura: arquivo não encontrado\n");
		exit(1); // força o encerramento do programa (POR CONVENÇÃO: retorna 0 caso tudo ocorra bem, retorna um número diferente de 0 caso ocorra um erro)
	}
	else
	{
		while (1)
		{
			letra = getchar();

			if (letra == '.') // enquanto não for digitado o ponto, continuará sendo lido
			{
				fputc('.', arq);
				break;
			}

			else
			{
				fputc(letra, arq); // inserir caractere ao arquivo
				// c = fgetc(arq);		ler o que foi inserido no arquivo [desativado pois a função fgetc() usa ponteiros]
			}
		}
	}

	fputc('*', stdout); // mostrar caractere na tela/interface

	printf("\n \n");

	c = fgetc(stdin); // ler o que está sendo digitado no teclado
	putchar(c); // imprimir o caractere que foi lido

	printf("\n");


	fclose(arq); // fechar arquivo e enviar tudo o que foi armazenado no buffer para o arquivo

	return 0; // retorna 0 ao sistema operacional, indicando o fim do programa
}

/*

	---------------- MODOS DE ABERTURA DE ARQUIVO ----------------

	MODO		TIPO_DE_ARQUIVO			FUNCIONALIDADE

	"r"			texto					Leitura. Arquivo deve existir ("read")
	"w"			texto					Escrita. Cria arquivo se não houver. Apaga o anterior se ele existir ("write")
	"a"			texto					Escrita. Os dados serão adicionados no fim do arquivo ("append")
	"r+"		texto					Leitura/Escrita. O arquivo deve existir e pode ser modificado
	"w+"		texto					Leitura/Escrita. Cria arquivo se não houver. Apaga o anterior se ele existir
	"a+"		texto					Leitura/Escrita. Os dados serão adicionados no fim do arquivo

	"rb"		binário					Leitura. Arquivo deve existir
	"wb"		binário					Escrita. Cria arquivo se não houver. Apaga o anterior se ele existir
	"ab"		binário					Escrita. Os dados serão adicionados no fim do arquivo
	"r+b"		binário					Leitura/Escrita. O arquivo deve existir e pode ser modificado
	"w+b"		binário					Leitura/Escrita. Cria arquivo se não houver. Apaga o anterior se ele existir
	"a+b"		binário					Leitura/Escrita. Os dados serão adicionados no fim do arquivo

*/
