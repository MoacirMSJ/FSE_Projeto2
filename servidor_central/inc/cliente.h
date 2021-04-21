#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define SERVIDOR_PORTA 10126
#define SERVIDOR_IP "192.168.0.4"

typedef struct entrada{
  char nome_aparelho[20];
  char instrucao[4];
  int posicao_vetor;
} Entrada;


void subMenu();
void bloqueiaImpressaoTempUmidade();
void desbloqueiaImpressaoTempUmidade();


int cliente_umidade_temperatura;
int cliente_usuario;

float temperatura, umidade;

pthread_t thread_cliente_usuario, thread_cliente_temp_umi;

pthread_mutex_t chave;

char cliente(char *mensagem, int tipoUsuario);
// void clienteUsuario(char *mensagem);







#endif /* CLIENTE_H_ */