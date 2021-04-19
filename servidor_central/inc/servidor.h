#ifndef SERVIDOR_H_
#define SERVIDOR_H_
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define PORTA 10026

bool alarme_ativado;
bool notificacao_recebida;



int servidorSocket, socketCliente;

void encerrarServidor();
void tocarAlarme();
void trataRequisicao(int socketCliente);
void servidor();



#endif /* SERVIDOR_H_*/