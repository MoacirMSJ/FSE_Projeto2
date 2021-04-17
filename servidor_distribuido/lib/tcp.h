#ifndef TCP_H_
#define TCP_H_

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

void servidor();
void cliente(char *mensagem);

#endif /* TCP_H_ */
