/*

Criptografia de Textos com Cifra Caesar (Maiusculas e Minusculas, com chave diferente)

Alvaro Davi, Eng Comp UFES, 2020

*/

#include <stdio.h>
#include <stdlib.h>

char Code(char word, int key);
char Decode(char word, int key);
char convertWord(char word);
int entreascii(char word);
int entreASCII(char word);

int main()
{
	int option, keyword;
	char word;

	scanf("%d ", &option);
	if (option == 1 || option == 2)
	{
		scanf("%d ", &keyword);

		while (1)
		{
			scanf("%c", &word);

			if (word == '.')
			{
				printf(".");
				break;
			}
			else
			{
				if (option == 1)
				{
					word = Code(word, keyword);
				}
				if (option == 2)
				{
					word = Decode(word, keyword);
				}
				printf("%c", word);
			}
		}
	}
	else
	{
		printf("Operacao invalida.");
	}

	return 0;
}

char Code(char word, int key)
{
	// word = convertWord(word);
	int wordTemp;

	if (entreascii(word))
	{
		wordTemp = word;

		key = key;
		word += key;

		if (! entreascii(word))
		{
			word = word - wordTemp;
		}
	}

	if (entreASCII(word))
	{
		wordTemp = word;

		key = 2 * key;
		word += key;

		if (! entreASCII(word))
		{
			word = word - wordTemp;
		}
	}

	else
	{
		word = word;
	}

	return word;
}

char Decode(char word, int key)
{
	// word = convertWord(word);
	int wordTemp;

	if (entreascii(word))
	{
		wordTemp = word;

		key = key;
		word -= key;

		if (! entreascii(word))
		{
			word = word - wordTemp;
		}
	}

	if (entreASCII(word))
	{
		wordTemp = word;

		key = 2 * key;
		word -= key;

		if (! entreASCII(word))
		{
			word = word - wordTemp;
		}
	}

	else
	{
		word = word;
	}

	return word;
}

char convertWord(char word)
{
	if (word >= 'A' && word <= 'Z')
	{
		word -= ('A' - 'a');	/*	word = word - ('A' - 'a') ---> (word - 32)	*/
	}
	else if (word >= 'a' && word <= 'z')
	{
		word = word;
	}
	else
	{
		word = word;
	}

	return word;
}

int entreascii(char word)
{
	return (word >= 'a' && word <= 'z');
}

int entreASCII(char word)
{
	return (word >= 'A' && word <= 'Z');
}
