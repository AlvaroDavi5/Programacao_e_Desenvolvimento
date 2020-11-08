#include <stdio.h>
#include <stdlib.h>

int main()
{
	char string[100]  = "Hello World! \n"; // array com 100 espaços

	fputs(string, stdout);

	return 0;
}