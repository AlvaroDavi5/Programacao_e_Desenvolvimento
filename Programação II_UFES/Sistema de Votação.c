/*

anular eleicao se
	id do eleitor se repetir
	numero de eleitores for maior que quantidade informada

anular voto se
	numero do candidato for inexistente

voto em branco se
	numero do candidato for 0

se qtd_votos_validos < qtd_votos_brancos + qtd_votos_nulos
	retornar que ninguem foi eleito e que sera necessario outra eleicao

se houver empate nos votos
	retornar que houve empate

-----------------------

ENTRADA:
  <qtd_eleitores>
  <id_eleitor> <numero_presidente> <numero_primeiro_ministro>
  ...
  P


SAIDA (eleicao anulada):
  ELEICAO ANULADA

SAIDA (eleicao valida):
  FIM DA ELEICAO
    - PRESIDENTE ELEITO: <nome_presidente> (<partido>), <total_de_votos>, <porcentagem_de_votos_validos>%
    - PRIMEIRO MINISTRO ELEITO: <nome_pm> (<partido>), <total_de_votos>, <porcentagem_de_votos_validos>%
    - COMPARECIMENTO: <porcentagem_de_pessoas_que_votaram>%
    - NULOS E BRANCOS: <total_nulos_brancos_presidente>, <total_nulos_brancos_pministro>

SAIDA (eleicao empatada pres OU min):
  FIM DA ELEICAO
    - PRESIDENTE ELEITO: EMPATE
    - PRIMEIRO MINISTRO ELEITO: EMPATE
    - COMPARECIMENTO: <porcentagem_de_pessoas_que_votaram>%
    - NULOS E BRANCOS: <total_nulos_brancos_presidente>, <total_nulos_brancos_pministro>

SAIDA (eleicao poucos votos validos pres OU min):
  FIM DA ELEICAO
    - PRESIDENTE ELEITO: SEM DECISAO
    - PRIMEIRO MINISTRO ELEITO: SEM DECISAO
    - COMPARECIMENTO: <porcentagem_de_pessoas_que_votaram>%
    - NULOS E BRANCOS: <total_nulos_brancos_presidente>, <total_nulos_brancos_pministro>

Saídas que são string devem ser maiúsculas e saídas float devem ter precisão de 2 casas decimais.

*/

#include <stdio.h>

int main()
{
	printf("Hello World\n");
	return 0;
}