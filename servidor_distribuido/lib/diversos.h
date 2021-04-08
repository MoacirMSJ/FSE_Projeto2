#ifndef DIVERSOS_H_
#define DIVERSOS_H_

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "tipos.h"
#include "lcd.h"
#include "log.h"
#include "bme280.h"
#include "uart.h"
#include "pwm.h"

#define RESISTORPWM 4
#define VENTOINHAPWM 5

void subMenu();
void alarme(int s);
void finaliza(int s);
void mensagemErro();
void mostrarDados(DadosUart dados, float tExterna, float temperaturaDesejada, PidDados pidAux);

#endif /* DIVERSOS_H_ */