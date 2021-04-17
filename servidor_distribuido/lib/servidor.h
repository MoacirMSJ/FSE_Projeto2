#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "pwm.h"
#include "monitoramento.h"
#include "bme280.h"


#define PORTA 10126

int servidorSocket, clienteSocket;


void servidor();


#endif /* SERVIDOR_H_ */
