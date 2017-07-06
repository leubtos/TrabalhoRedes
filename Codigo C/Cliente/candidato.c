#include "candidato.h"


void nomeEpartido(char **listaNomes, char **listaPartidos, int quantidade)
{
	int i;

	for (i = 0; i < 2; i++)
	{
		listaNomes[i] = (char*)malloc(sizeof(char));
		listaPartidos[i] = (char*)malloc(sizeof(char));
	}


	//Para adicionar mais candidatos mudar aqui e a Quantidade(int) de candidatos.
	char *aux = (char*)malloc(50 * sizeof(char));
	strcpy(aux, "Roni\0");
	strcpy(listaNomes[0], aux);

	strcpy(aux, "Brenda\0");
	strcpy(listaNomes[1], aux);


	strcpy(aux, "BSI\0");
	strcpy(listaPartidos[0], aux);

	strcpy(aux, "Poligota\0");
	strcpy(listaPartidos[1], aux);

}

CANDIDATO *criarCandidato(int codigo, char *nome, char *partido)
{
	CANDIDATO *novoCandidato = (CANDIDATO*)malloc(sizeof(CANDIDATO));
	novoCandidato->codigo = codigo;

	novoCandidato->nome = (char*)malloc(TAM_NOME * sizeof(char));
	strcpy(novoCandidato->nome, nome);
	strcat(novoCandidato->nome, "\0");
	
	novoCandidato->partido = (char*)malloc(TAM_PARTIDO * sizeof(char));
	strcpy(novoCandidato->partido, partido);
	strcat(novoCandidato->partido, "\0");

	novoCandidato->qtdVotos = 0;

	return novoCandidato;
}

int verificaExistencia(CANDIDATO **candidatos, int codigo, int qtdCandidatos)
{
	int i;

	for(i = 0; i < qtdCandidatos; i++)
	{
		if((*candidatos[i]).codigo == codigo)
		{
			return 1;// Candidato com o codigo em quest�o existe.
		}
	}

	return 0;// candidato n�o existe.
}

void imprimirCandidatos(CANDIDATO **candidatos, int qtdCandidatos)
{
	int i;

	for(i = 0; i < qtdCandidatos; i++)
	{
		printf("\n");
		printf("Codigo: %d\n", (*candidatos[i]).codigo);
		printf("Nome: %s\n", (*candidatos[i]).nome);
		printf("partido: %s\n", (*candidatos[i]).partido);
	}

}



char *strcpym(char *dest, char *orig)
{
	int i;

	for (i = 0; i < strlen(orig); i++)
		dest[i] = orig[i];


	dest[i] = '\0';


	return dest;
}

void gerarDados(int quantidade, int *codigos, char **nomes, char **partidos, char **listaNomes, char **listaPartidos)
{
    int i;
	

    for(i = 0; i < quantidade; i++)
    {
        codigos[i] = i;
        nomes[i] = (char*)malloc(50 * sizeof(char));
		
        partidos[i] = (char*)malloc(50 * sizeof(char));
		
    }

	strcpym(nomes[0], listaNomes[0]);
	strcpym(nomes[1], listaNomes[1]);
	strcpym(partidos[0], listaPartidos[0]);
	strcpym(partidos[1], listaPartidos[1]);   
}

CANDIDATO **gerarListaCandidatos(int quantidade, int *codigos, char **nomes, char **partidos)
{
    int i;
    CANDIDATO **candidatos = (CANDIDATO**)malloc(quantidade * sizeof(CANDIDATO*));

    for(i = 0; i < quantidade; i++)
    {
        candidatos[i] = criarCandidato(codigos[i], nomes[i], partidos[i]);

    }

    return candidatos;
}

void receberCandidatos(CANDIDATO **candidatos, int qtdCandidatos)
{

}

void enviarCandidatos(CANDIDATO **candidatos, int qtdCandidatos)
{
}
