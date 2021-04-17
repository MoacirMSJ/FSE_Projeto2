#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "defines.h"

void notificar(void);
int monitoraSensorEntrada(int pino);
int monitorarTodosPinos();