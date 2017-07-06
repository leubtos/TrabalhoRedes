#ifndef _CANDIDATO_H_
#define _CANDIDATO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOME 50
#define TAM_PARTIDO 50

typedef struct candidato
{
	int codigo;
	char *nome;
	char *partido;
	int qtdVotos;
}CANDIDATO;

void nomeEpartido(char **listaNomes, char **listaPartidos, int quantidade);
CANDIDATO *criarCandidato(int codigo, char *nome, char *partido);
int verificaExistencia(CANDIDATO **candidatos, int codigo, int qtdCandidatos);
void imprimirCandidatos(CANDIDATO **candidatos, int qtdCandidatos);
void gerarDados(int quantidade, int *codigos, char **nomes, char **partidos, char **listaNomes, char **listaPartidos);
CANDIDATO **gerarListaCandidatos(int quantidade, int *codigos, char **nomes, char **partidos);
void receberCandidatos(CANDIDATO **candidatos, int qtdCandidatos);
void enviarCandidatos(CANDIDATO **candidatos, int qtdCandidatos);



#endif //_CANDIDATO_H_
