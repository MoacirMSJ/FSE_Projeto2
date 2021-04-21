#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include "log.h"
#include "i2c.h"
#include "gpio.h"
#include "diversos.h"
#include "servidor.h"

int main(){
  signal(SIGINT,finaliza); 
  printf("Iniciando servidor Distribuido\n");
  if(criarPinosPWM()< 0){
    printf("Erro ao criar pinos\n");
  }
  servidor();
  return 0;
}


