/*

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

typedef struct
{
	int nulo;
	int branco;
	int dijkstra;
	int turing;
	int shaw;
} tCandPres;

typedef struct
{
	int nulo;
	int branco;
	int berners_lee;
	int torvalds;
	int lovelace;
} tCandMin;


tCandPres contabilizadorPres(int num_pres, tCandPres candidatosP);
tCandMin contabilizadorMin(int num_min, tCandMin candidatosM);
int excessoDeVotos(int qtd_control, int qtd_eleitores);
float percentValid(int votos_validos, int total_votos);
float percentComp(int qtd_control, int qtd_eleitores);
void anulaEleicao();
void imprimeEleValida(tCandPres candidatosP, tCandMin candidatosM, int qtd_control, int qtd_eleitores, int votos_validosP, int votos_invalidosP, int votos_validosM, int votos_invalidosM);
int EleSemDecisao(int invalidos, int validos);
void verifGanhadorP(tCandPres candidatosP);
void verifGanhadorM(tCandMin candidatosM);
void mostrarVencedor(int vencedor);


int main()
{
	tCandPres candidatosP;
	tCandMin candidatosM;

	int qtd_eleitores, qtd_control = 0;
	int id_eleitor, id_temp = 0, num_pres, num_min;

	int votos_validosP = 0, votos_invalidosP = 0;
	int votos_validosM = 0, votos_invalidosM = 0;
	int verificador = 0;

	scanf("%d", &qtd_eleitores);

	while (scanf("%d %d %d", &id_eleitor, &num_pres, &num_min) == 3)
	{
		if (id_temp == 0)
		{
			id_temp = id_eleitor;
		}
		else
		{
			if (id_temp == id_eleitor)
			{
				anulaEleicao();
			}
			else
			{
				id_temp = id_eleitor;
			}
		}

		qtd_control++;

		if (excessoDeVotos(qtd_control, qtd_eleitores))
		{
			anulaEleicao();
		}
		else
		{
			candidatosP = contabilizadorPres(num_pres, candidatosP);
			candidatosM = contabilizadorMin(num_min, candidatosM);


			votos_validosP = candidatosP.dijkstra + candidatosP.turing + candidatosP.shaw;
			votos_invalidosP = candidatosP.branco + candidatosP.nulo;

			votos_validosM = candidatosM.berners_lee + candidatosM.torvalds + candidatosM.lovelace;
			votos_invalidosM = candidatosM.branco + candidatosM.nulo;

			verificador = 1;
		}
	}

	if (verificador == 1)
	{
		imprimeEleValida(candidatosP, candidatosM, qtd_control, qtd_eleitores, votos_validosP, votos_invalidosP, votos_validosM, votos_invalidosM);
	}

	return 0;
}


tCandPres contabilizadorPres(int num_pres, tCandPres candidatosP)
{
	tCandPres candidato = candidatosP;

	switch (num_pres)
	{
	case 0:
		candidato.branco++;
		break;
	case 10:
		candidato.dijkstra++;
		break;
	case 42:
		candidato.turing++;
		break;
	case 26:
		candidato.shaw++;
		break;
	default:
		candidato.nulo++;
		break;
	}

	return candidato;
}

tCandMin contabilizadorMin(int num_min, tCandMin candidatosM)
{
	tCandMin candidato = candidatosM;

	switch (num_min)
	{
	case 0:
		candidato.branco++;
		break;
	case 36:
		candidato.berners_lee++;
		break;
	case 64:
		candidato.torvalds++;
		break;
	case 18:
		candidato.lovelace++;
		break;
	default:
		candidato.nulo++;
		break;
	}

	return candidato;
}

void verifGanhadorP(tCandPres candidatosP)
{
	int nulo = candidatosP.nulo;
	int branco = candidatosP.branco;
	int Dijkstra = candidatosP.dijkstra;
	int Turing = candidatosP.turing;
	int Shaw = candidatosP.shaw;

	int maior;
	int vencedor;

	if (Dijkstra >= Turing)
	{
		if (Dijkstra == Turing)
		{
			maior = Dijkstra;
			vencedor = 0;
		}
		else
		{
			maior = Dijkstra;
			vencedor = 10;
		}
	}
	else
	{
		maior = Turing;
		vencedor = 42;
	}

	if (Shaw > maior)
	{
		maior = Shaw;
		vencedor = 26;
	}
	if (Shaw == maior)
	{
		vencedor = 0;
	}

	mostrarVencedor(vencedor);
}

void verifGanhadorM(tCandMin candidatosM)
{
	int nulo = candidatosM.nulo;
	int branco = candidatosM.branco;
	int Tim = candidatosM.berners_lee;
	int Torvalds = candidatosM.torvalds;
	int Lovelace = candidatosM.lovelace;

	int maior;
	int vencedor;

	if (Tim >= Torvalds)
	{
		if (Tim == Torvalds)
		{
			maior = Tim;
			vencedor = 0;
		}
		else
		{
			maior = Tim;
			vencedor = 36;
		}
	}
	else
	{
		maior = Torvalds;
		vencedor = 64;
	}

	if (Lovelace > maior)
	{
		maior = Lovelace;
		vencedor = 18;
	}
	if (Lovelace == maior)
	{
		vencedor = 0;
	}

	mostrarVencedor(vencedor);
}

void mostrarVencedor(int vencedor)
{
	switch (vencedor)
	{
	case 10:
		printf("Edsger Dijkstra (Partido do Melhor Caminho (PMC))");
		break;
	case 42:
		printf("Alan Turing (Partido dos Avanço Intelectual (PAI))");
		break;
	case 26:
		printf("Carol Shaw (Gamers Unidos (GU))");
		break;
	case 36:
		printf("Tim Berners-Lee (World Wide Web (WWW))");
		break;
	case 64:
		printf("Linus Torvalds (Linux (Linux))");
		break;
	case 18:
		printf("Ada Lovelace (Mulheres Programadoras Unidas (MPU))");
		break;
	default:
		printf("EMPATE");
		break;
	}
}

int excessoDeVotos(int qtd_control, int qtd_eleitores)
{
	if (qtd_control > qtd_eleitores)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

float percentValid(int votos_validos, int total_votos)
{
	float percent;
	percent = (100.0 * votos_validos) / total_votos;

	return percent;
}

float percentComp(int qtd_control, int qtd_eleitores)
{
	float percent;
	percent = (100.0 * qtd_control) / qtd_eleitores;

	return percent;
}

int EleSemDecisao(int invalidos, int validos)
{
	if (validos < invalidos)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void anulaEleicao()
{
	printf("ELEICAO ANULADA");
	exit(0);
}

void imprimeEleValida(tCandPres candidatosP, tCandMin candidatosM, int qtd_control, int qtd_eleitores, int votos_validosP, int votos_invalidosP, int votos_validosM, int votos_invalidosM)
{
	printf("FIM DA ELEICAO\n");
	printf("- PRESIDENTE ELEITO: ");
	if (EleSemDecisao(votos_invalidosP, votos_validosP))
	{
		printf("SEM DECISAO");
	}
	else
	{
		verifGanhadorP(candidatosP);
		printf(", %d", qtd_control);
		float percentVVP = percentValid(votos_validosP, qtd_eleitores);
		printf(", %.2f%%", percentVVP);
	}
	printf("\n");


	printf("- PRIMEIRO MINISTRO ELEITO: ");
	if (EleSemDecisao(votos_invalidosM, votos_validosM))
	{
		printf("SEM DECISAO");
	}
	else
	{
		verifGanhadorM(candidatosM);
		printf(", %d", qtd_control);
		float percentVVM = percentValid(votos_validosM, qtd_eleitores);
		printf(", %.2f%%", percentVVM);
	}
	printf("\n");


	float percent = percentComp(qtd_control, qtd_eleitores);
	printf("- COMPARECIMENTO: %.2f%%\n", percent);

	printf("- NULOS E BRANCOS: %d, %d", votos_invalidosP, votos_invalidosM);
}
