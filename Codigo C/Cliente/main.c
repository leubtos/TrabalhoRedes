/* Cliente */ 

/* Arquivo: cl.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "candidato.h"

#define TAM_BUFFER 1024
#define porta 2525
int main ()
{

    char ip[16], buffer[TAM_BUFFER], bufaux[TAM_BUFFER];
    int tbuf, skt, i;
    int qtdCandidatos = 2;
    struct sockaddr_in serv;
    
    system("clear");
    
    printf("\nUrna\n");
    
    printf("\n>> Diegite o ip do Servidor ou /x para sair: ");
    strcpy(ip,"192.168.80.129");
    //gets(ip);
    
    skt = socket(AF_INET, SOCK_STREAM, 0);
    
    serv.sin_family = AF_INET; 
    serv.sin_addr.s_addr = inet_addr(ip); 
    serv.sin_port = htons (porta); 

    memset (&(serv.sin_zero), 0x00, sizeof (serv.sin_zero));
    if(connect (skt, (struct sockaddr *)&serv, sizeof (struct sockaddr)) != 0) 
    {
        puts("\n> Servidor nao Encontrado\n");
        exit(0);
    
    }
    printf(">> A Conexao com o Servidor %s foi estabelecida na porta %d \n\n",ip,porta);
   /* // Recebe ack do serv
    tbuf = recv (skt, buffer, TAM_BUFFER, 0);
    buffer[tbuf] = 0x00;
    printf (">: %s\n",buffer);

    // Envia ack p/ serv
    strcpy(buffer, "Client comunicando OK!!!");
    send(skt, buffer, strlen(buffer), 0 );    
    */
    
    CANDIDATO **candidatos = (CANDIDATO**)malloc(qtdCandidatos * sizeof(CANDIDATO*));
    for(i = 0; i < qtdCandidatos; i++)
    {
        candidatos[i] = (CANDIDATO*)malloc(sizeof(CANDIDATO));
        candidatos[i]->nome = (char*)malloc(50 * sizeof(char));
        candidatos[i]->partido = (char*)malloc(50 * sizeof(char));
        candidatos[i]->qtdVotos = 0;
    }

    int opcao = 0;
    int codigoCandidato = -1;
    int votou = 0;
    int listaCarregada = 0;
    int votosNulos = 0, votosBrancos = 0;
    char *aux = (char*)malloc(5 * sizeof(char));

    while(1)
    {
       

        printf("\n1: Votar.\n");
        printf("2: Votar Nulo.\n");
        printf("3: votar Branco.\n");
        printf("999: Carregar a Lista de candidatos do servidor.\n");
        printf("888: Enviar dados e finalizar sessao.\n");

        fflush(stdin);
	    scanf("%d", &opcao);

        //gets(buffer);
       // strcpy(bufaux,buffer);

        ///----------------VOTAR---------------///
        if (opcao == 1)
        {
            if(listaCarregada == 1)
            {
                fflush(stdin);
                printf("\nDigite o codigo do candidato: ");
                scanf("%d", &codigoCandidato);
                if(verificaExistencia(candidatos, codigoCandidato, 2) == 1)
                {
                    printf("candidato: %s", candidatos[codigoCandidato]->nome);
                    candidatos[codigoCandidato]->qtdVotos++;
                    votou = 1;
                }

                else
                {
                    printf("\nNão existe candidato com esse codigo");
                }
            }
            
            else
            {
                printf("\nLista de candidatos nao carregada");
            }
        }

        ///--------------VOTAR NULO --------------///
        else if (opcao == 2)
        {
            printf("\nVoto Nulo");
            votosNulos++;

        }

        ///--------------VOTAR BRANCO --------------///
        else if (opcao == 3)
        {
            printf("\nVoto Branco");
            votosBrancos++;

        }

        else if(opcao == 4)
        {
            strcpy(buffer, "4");
            send(skt, buffer, strlen(buffer), 0);
        }


        ///----------------- CARREGAR LISTA-------------///
        else if (opcao == 999)
        {
            if(listaCarregada == 0)
            {
                strcpy(buffer, "999");
                send(skt, buffer, strlen(buffer), 0);

                printf("\ncarregando lista\n");
                for( i = 0; i < qtdCandidatos; i++)
                {
                    recv(skt, aux, 1024,0);

                    candidatos[i]->codigo = atoi(aux);
                    //printf("\ncodigo: %d e aux: %s", candidatos[i]->codigo, aux);

                    strcpy(buffer, "1");
                    send(skt, buffer, 1, 0);

                    recv(skt, candidatos[i]->nome, 50, 0);
                    //printf("\nnome: %s", candidatos[i]->nome);

                    strcpy(buffer, "1");
                    send(skt, buffer, 1, 0);

                    recv(skt, candidatos[i]->partido, 50, 0);
                   // printf("\nPartido: %s", candidatos[i]->partido);                    
                }

                listaCarregada = 1;
                printf("\nLista Carregada.\n");
            }
            else 
            {
                printf("\nLista de candidatos ja foi carregada\n");
            }
        }

        ///-------------Enviar dados e finalizar Sessao ----------///
        else if (opcao == 888)
        {
            if(votou == 1)
            {
                strcpy(buffer,"888");
                send(skt, buffer, strlen(buffer), 0);
                
                //ACK
                recv(skt, aux, 1, 0);
                if(strcmp(aux, "1") == 0)
                {
                    sprintf(buffer, "%i", votosNulos);
                    send(skt, buffer, strlen(buffer), 0);
                }
                
                //ACK
                recv(skt, aux, 1, 0);
                if(strcmp(aux, "1") == 0)
                {
                    sprintf(buffer, "%i", votosBrancos);
                    send(skt, buffer, strlen(buffer), 0);
                }
                
                //ACK
                recv(skt, aux, 1, 0);
                if(strcmp(aux, "1") == 0)
                {
                    for(i = 0; i < qtdCandidatos; i++)
                    {   
                        char *aux = (char*)malloc(5 * sizeof(char));
                        sprintf(aux, "%i", candidatos[i]->codigo);
                        send(skt, aux, strlen(aux), 0);

                        //ACK
                        recv(skt, aux, 1, 0);
                        if(strcmp(aux, "1") == 0)
                        {
                            sprintf(aux, "%i", candidatos[i]->qtdVotos);
                            send(skt, aux, strlen(aux), 0);

                        }

                        if(strcmp(aux, "1") == 0)
                        {
                            continue;
                        }
                     }
                }
                //break;
            }
            else
            {
                printf("\nnao existe alteracoes a serem enviadas");
            }
        
        }   
    }
        close(skt);
        printf (">>A conexao com o servidor foi finalizada!!!\n\n");

        free(aux);
        return 0;
}
