#include <stdio.h>
#include <stdlib.h>

int main()
{
	char string[100]  = "Hello World! \n"; // array com 100 espaços
	// string[100] = {'O', 'l', 'a', ',', 'm', 'u', 'n', 'd', 'o', '!'};

	fputs(string, stdout); // printar no terminal (arquivo padrão stdout)

	return 0;
}
