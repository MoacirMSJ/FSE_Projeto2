#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include "defines.h"


#define SERV_CENTRAL_PORTA 10026
#define SERV_CENTRAL_IP "192.168.0.53"

int cliente_Socket;

void notificar(void);
int monitoraSensorEntrada(int pino);
int monitorarTodosPinos();
void cliente(char *mensagem);