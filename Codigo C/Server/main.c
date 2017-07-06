#include "servidor.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int qtdCandidatos = 2;
	
	char **listaNomes = (char**)malloc(2 * sizeof(char*));
	char **listaPartidos = (char**)malloc(2 * sizeof(char*));
	int *codigos = (int*)malloc(qtdCandidatos * sizeof(int));
	char **nomes = (char**)malloc(qtdCandidatos * sizeof(char*));
	char  **partidos = (char**)malloc(qtdCandidatos * sizeof(char*));

	//Função que inicializa as listas de Nomes e Partidos.
	nomeEpartido(listaNomes, listaPartidos, qtdCandidatos);

	//Função que iniciializa as variáveis com as informações que estão nas listas de nome e partido.
	gerarDados(qtdCandidatos, codigos, nomes, partidos, listaNomes, listaPartidos);

	//Gera os candidatos.
    CANDIDATO **candidatos = gerarListaCandidatos(qtdCandidatos, codigos, nomes, partidos);

    servidor(candidatos, qtdCandidatos);

    return 0;
}