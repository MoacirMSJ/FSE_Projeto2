#include "pwm.h"


int criarPinosPWM(int pino1, int modo){
  wiringPiSetup();
  if(modo == 1){
    pinMode(pino1, INPUT);
  }
  else{
    pinMode(pino1, OUTPUT);
  }
  

  if(softPwmCreate (pino1, 0, 100) !=0){
    printf("Erro ao criar pino PWM %d.\n",pino1);
    return -1;
  }

  return 1;
}

void enviarIntensidadePWM(int pino, int pid_intensidade){
  softPwmWrite (pino, pid_intensidade);
}

int retornarValorPino(int pino){
  return digitalRead(pino);
}

void zeraIntensidadePWM(int pino1){
  softPwmWrite (pino1, 0);
  // printf("-> Ventoinha e resistor desligaods...\n");
}

// int w = wiringPiSetup();
//     if(w < 0){
//         printf("erro ao iniciar wiringPi");
//         exit(1);
//     }

//     pinMode(pino,OUTPUT);
//     softPwmCreate(pino,0,100);
//     softPwmWrite(pino, pwm);