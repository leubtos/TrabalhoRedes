#include "servidor.h"

void servidor(CANDIDATO **candidatos, int qtdCandidatos)
{
    struct sockaddr_in server;
    char ip[16];
    char buffer[TAM_BUFFER];
    int sock, length;
    int msgsock;
    int rval;
	int tbuf;
	int teste;

	char *aux = (char*)malloc(5 * sizeof(char));
	char *aux2 = (char*)malloc(10 * sizeof(char));

	int  votosBrancos = 0, votosNulos = 0;
	int i;

    //Cria o socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) 
    {
        perror("opening stream socket");
        exit(1);
    }

	//Inicializando as variáveis do socket
    bzero (&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons (porta);
    
    if (bind(sock, (struct sockaddr *) &server, sizeof server) == -1)
    {
        perror("binding stream socket");
        exit(1);
    }

    /// Descobre a porta utilizada
    length = sizeof server;
    if (getsockname(sock,(struct sockaddr *) &server, &length) == -1)
    {
        perror("getting socket name");
        exit(1);
    }
    
    printf("Porta do Socket: %d\n", ntohs(server.sin_port));
    ///O servidor começa a aceitar conexões
    listen(sock, 5);
    do 
	{
        msgsock = accept(sock,(struct sockaddr *) 0,(int *) 0);
		printf("\nCliente se conectou\n");
        if (msgsock == -1)
		{
            perror("accept");
		}

        else do
		{
        	while(1)
			{
				
				///verifica entrada que vem do cliente.	
				tbuf = recv(msgsock, buffer, TAM_BUFFER, 0);
				buffer[tbuf] = 0x00;

				if(strcmp(buffer,"999") == 0)
				{
					printf("\nEnviando dados para o cliente...");
					for(i = 0; i < qtdCandidatos; i++)
					{
						
						sprintf(aux, "%i", candidatos[i]->codigo);
						send(msgsock, aux, strlen(aux), 0);

						//ACK
						recv(msgsock, aux, 1024, 0);
						if(strcmp(aux, "1") == 0)
						{
							send(msgsock, candidatos[i]->nome, strlen(candidatos[i]->nome), 0);
						}

						//ACK
						recv(msgsock, aux, 1024, 0);
						if(strcmp(aux, "1") == 0)
						{
							send(msgsock, candidatos[i]->partido, strlen(candidatos[i]->partido), 0);
						}
					}
					
					printf("\n-------Dados ja enviados--------\n");
					//printf("\n");
				}

				else if(strcmp(buffer, "888") == 0)
				{
					//ACK
					strcpy(aux, "1");
					send(msgsock, aux, 1, 0);

					//votos Nulos
					recv(msgsock, aux2, 1024, 0);
					votosNulos += atoi(aux2);

					//Votos Brancos 
					send(msgsock, aux, 1, 0);
					recv(msgsock, aux2, 1024, 0);
					votosBrancos += atoi(aux2);

					send(msgsock, aux, 1, 0);
					int indiceAuxiliar = 0;
					for(i = 0; i <qtdCandidatos; i++)
					{
						recv(msgsock, aux2, 1024, 0);
						indiceAuxiliar = atoi(aux2);//Codigo do candidato
						send(msgsock, aux, 1, 0);

						recv(msgsock, aux2, 50, 0);
						candidatos[indiceAuxiliar]->qtdVotos += atoi(aux2);//Qtd de votos 
						send(msgsock, aux, 1, 0);
						
					}

					close(msgsock);
					printf("\nfechou o socket");
					printf("\n");
					teste = 1;
					break;				
				}

				else if(strcmp(buffer, "4") == 0)
				{
					printf("\nVotos nulos: %d", votosNulos);
					printf("\nVotos Brancos: %d", votosBrancos);
					printf("\n\n***********Candidatos************\n");
					for(i = 0; i < qtdCandidatos; i++)
					{
						printf("\nCodigo: %d", candidatos[i]->codigo);
						printf("\nNome: %s", candidatos[i]->nome);
						printf("\nPartido: %s", candidatos[i]->partido);
						printf("\nqtdVotos: %d\n", candidatos[i]->qtdVotos);
						printf("*********************************");

					}
				}

				else if(strcmp(buffer, "5") == 0)
				{
					printf("\nlimpando os votos\n");
					votosBrancos = 0;
					votosNulos = 0;

					for(i = 0; i < qtdCandidatos; i++)
					{						
						candidatos[i]->qtdVotos = 0;
					}
				}

				strcpy(buffer, "0");
			}
		/*if ((rval = read(msgsock, buffer, sizeof(buffer))) == -1)
            perror("reading stream message");
                    
        if (rval == 0)
            printf("Finalizando conexao\n");
*/
			strcpy(buffer, "0");
			if(teste == 1)
			{
				strcpy(buffer, "0");			
				break;
			}

		} while (1);
        close(msgsock);
    } while(TRUE);
}


