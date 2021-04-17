#include "pwm.h"

#define SAIDA 0
#define ENTRADA 1
//modo 0 pino tipo entrada modo 1 pino saida
int criarPinosPWM(){

  wiringPiSetup();
  // Pinos de saida
  pinMode(LAP_COZINHA, OUTPUT);
  softPwmCreate (LAP_COZINHA, LOW, HIGH);
  
  pinMode(LAP_SALA, OUTPUT);
  softPwmCreate (LAP_SALA, LOW, HIGH);
  
  pinMode(LAP_QUARTO_1, OUTPUT);
  softPwmCreate (LAP_QUARTO_1, LOW, HIGH);

  pinMode(LAP_QUARTO_2, OUTPUT);
  softPwmCreate (LAP_QUARTO_2, LOW, HIGH);

  pinMode(AR_1, OUTPUT);
  softPwmCreate (AR_1, LOW, HIGH);

  pinMode(AR_2, OUTPUT);
  softPwmCreate (AR_2, LOW, HIGH);


  //pinos de entrada
  pinMode(SP_SALA, INPUT);
  pinMode(SP_COZINHA, INPUT);
  pinMode(SA_PORTA_COZINHA, INPUT);
  pinMode(SA_JANELA_COZINHA, INPUT);
  pinMode(SA_PORTA_SALA, INPUT);
  pinMode(SA_JANELA_SALA, INPUT);
  pinMode(SA_JANELA_QUARTO_1, INPUT);
  pinMode(SA_JANELA_QUARTO_2, INPUT);
  
  return 1;
}

void enviarIntensidadePWM(int pino, int pid_intensidade){
  softPwmWrite(pino, pid_intensidade);
}

int retornarValorPino(int pino){
  return digitalRead(pino);
}

void zeraIntensidadePWM(int pino1){
  softPwmWrite (pino1, LOW);
  // printf("-> Ventoinha e resistor desligaods...\n");
}


void desligaAparelhos(){
  softPwmWrite(LAP_COZINHA, LOW);
  softPwmWrite(LAP_SALA, LOW);
  softPwmWrite(LAP_QUARTO_1, LOW);
  softPwmWrite(AR_1, LOW);
  softPwmWrite(AR_2, LOW);

}

int verificaSeSensolesEstaoDesligados(){

   return (digitalRead(SP_SALA) + digitalRead(SP_COZINHA) 
            + digitalRead(SA_PORTA_COZINHA) +digitalRead(SA_JANELA_COZINHA) 
            + digitalRead(SA_PORTA_SALA) + digitalRead(SA_JANELA_SALA)
            + digitalRead(SA_JANELA_QUARTO_1) + digitalRead(SA_JANELA_QUARTO_2)
          );
}

