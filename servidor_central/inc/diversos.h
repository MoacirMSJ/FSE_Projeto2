#ifndef DIVERSOS_H_
#define DIVERSOS_H_

#include <stdio.h>
#include <pthread.h>
#include "cliente.h"
#include <signal.h>
#include "servidor.h"

pthread_t auxiliar;
pthread_t threadMonitoramento;
pthread_t teste;

void mostrarStatus();
Entrada subMenuLampada();
Entrada subMenuAr();
void* enviaComando(void *entrada);
void gerenciaAlarme();
void finaliza(int s);
int menu();
void * solicitaTempUmidade(void *test);
void  *solicitacaoUsuario(void *teste);
void abreMenu();
void* monitoramento(void *s);

#endif /* DIVERSOS_H_*/