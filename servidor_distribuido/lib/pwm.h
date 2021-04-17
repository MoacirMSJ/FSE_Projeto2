#ifndef PWM_H_
#define PWM_H_

#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

int lampadas[4] = {17,18,27,22};
int arCondicionados[2] = {13,19}
int sensorPresenca[2]= {25,26};
int sensorAbertura[6]= {5,6,12,16,20,21};

int criarPinosPWM(int pino1, int modo);
void enviarIntensidadePWM(int pino, int pid_intensidade);
int retornarValorPino(int pino);
void zeraIntensidadePWM(int pino1);
void criarVariosPinos();
void desligaTudo();


#endif /* PWM_H_ */