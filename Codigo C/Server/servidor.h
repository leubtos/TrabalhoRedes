#ifndef _SERVIDOR_H_
#define _SERVIDOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "candidato.h"
#define TRUE 1
#define TAM_BUFFER 1024
#define porta 40005


void servidor(CANDIDATO **candidatos, int qtdCandidatos);

#endif //_SERVIDOR_H_


