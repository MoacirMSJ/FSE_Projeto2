#include "pwm.h"

#define SAIDA 0
#define ENTRADA 1
//modo 0 pino tipo entrada modo 1 pino saida
int criarPinosPWM(int pino1, int modo){
  wiringPiSetup();
  if(modo == 1){
    pinMode(pino1, INPUT);
  }
  else{
    pinMode(pino1, OUTPUT);
    if(softPwmCreate (pino1, LOW, HIGH ) !=0){
      printf("Erro ao criar pino PWM %d.\n",pino1);
      return -1;
    }
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
  softPwmWrite (pino1, LOW);
  // printf("-> Ventoinha e resistor desligaods...\n");
}

void criarVariosPinos(){

  for(int i =0;i<4; i++){
    if(criarPinosPWM(lampadas[i],SAIDA)== -1 ){
      printf("Erro ao criar pinos de lampadas %d\n",lampadas[i]);
    }
  }

  for(int i =0;i<2; i++){
    if(criarPinosPWM(arCondicionados[i],SAIDA)== -1 ){
      printf("Erro ao criar pinos de ar-condicionados %d\n",arCondicionados[i]);
    }
    if(criarPinosPWM(sensorPresenca[i],ENTRADA)== -1 ){
      printf("Erro ao criar pinos de sensor presenca %d\n",sensorPresenca[i]);
    }
  }

  for(int i =0;i<6; i++){
    if(criarPinosPWM(sensorAbertura[i],ENTRADA)== -1 ){
      printf("Erro ao criar pinos de sensor abertura %d\n",sensorAbertura[i]);
    }
  }

}

void desligaTudo(){
  for(int i =0;i<4; i++){
    zeraIntensidadePWM(lampadas[i]);
    printf("Desligada Lampada: %d\n",lampadas[i]);
    
  }
  for(int i =0;i<2; i++){
    zeraIntensidadePWM(arCondicionados[i])
    printf("Desligado Ar-condicionado: %d\n",arCondicionados[i]);
    
    
  }

}


// int w = wiringPiSetup();
//     if(w < 0){
//         printf("erro ao iniciar wiringPi");
//         exit(1);
//     }

//     pinMode(pino,OUTPUT);
//     softPwmCreate(pino,0,100);
//     softPwmWrite(pino, pwm);