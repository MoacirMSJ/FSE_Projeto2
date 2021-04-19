#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
// #include "log.h"
// #include "bme280.h"
// #include "uart.h"
// #include "pid.h"
// #include "pwm.h"
// #include "tipos.h"
// #include "diversos.h"
#include "servidor.h"



float temperaturaDesejada;
char modo;
float tExterna;
// DadosLog log;


int main(){
  printf("Iniciando servidor Distribuido\n");
  // if(criarPinosPWM()< 0){
  //   printf("Erro ao criar pinos\n");
  // }
  servidor();
  return 0;
}


