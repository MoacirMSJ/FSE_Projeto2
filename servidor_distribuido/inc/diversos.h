#ifndef DIVERSOS_H_
#define DIVERSOS_H_

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "tipos.h"
#include "log.h"
#include "gpio.h"
#include "i2c.h"



#define RESISTORPWM 4
#define VENTOINHAPWM 5

void subMenu();
void alarme(int s);
void finaliza(int s);
void mensagemErro();

#endif /* DIVERSOS_H_ */