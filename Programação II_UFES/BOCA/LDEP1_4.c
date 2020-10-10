/*

Mostrar sequencia de primos ate um dado numero

Alvaro Davi, Eng Comp UFES, 2020

*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
  int i = 0, den = 0, primo = 0, qtd = 0, cont = 0;

  scanf("%d", &qtd);

  for(i = 2; i <= qtd; i++)
  {
    while(den <= i)
    {
      if((cont == 2) || (cont == 3) || (cont == 5) || (cont == 7))
      {
        printf("%d ", cont);
      }
      cont++;

      den++;
    }

    if((i % 2 != 0) && (i % 3 != 0) && (i % 5 != 0) && (i % 7 != 0))
    {
      printf("%d ", i);
    }

  }

  return 0;
}

/*

#include <stdio.h>

int main()
{
  int i = 0, den = 0, primo = 0, qtd = 0, cont = 0;

  scanf("%d", &qtd);

  for (i = 2; i < qtd; i++)
  {
    den += 2;
    while(den < i)
    {
      if ((i % den) == 0)
      {
        cont++;
        break;
      }
    }

    if ((cont % 2) == 0)
    {
      printf("%d", i);
    }
  }

  return 0;
}

*/