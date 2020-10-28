#include <stdio.h>
#include <math.h>

typedef struct /* tipo composto */
{
  int idade;
  float nota; // tipos primitivos compondo o struct
  int matricula;
} tEstudante; // atribui o nome 'tEstudante' para o tipo composto struct (em escopo global) ao mesmo tempo em que serve de identificador ao struct referido

int main()
{
  tEstudante aluno; // define o tipo da variável 'aluno' como o struct 'tEstudante'

  aluno.idade = 18; // acessa a variável idade da variável aluno, definida no struct
  aluno.nota = 9.5;
  aluno.matricula = 20201010;

  printf("%i %.2f %i", aluno.idade, aluno.nota, aluno.matricula);

	return 0;
}