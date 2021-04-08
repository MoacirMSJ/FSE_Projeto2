#ifndef PWM_H_
#define PWM_H_

#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

int criarPinosPWM(int pino1, int modo);
void enviarIntensidadePWM(int pino, int pid_intensidade);
int retornarValorPino(int pino);
void zeraIntensidadePWM(int p1);


#endif /* PWM_H_ */