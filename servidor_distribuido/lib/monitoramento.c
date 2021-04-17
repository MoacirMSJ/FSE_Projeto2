#include "monitoramento.h"


void notificar(void) {
  cliente("9:Alarme");
}


int monitoraSensorEntrada(int pino) {
  if (wiringPiSetup () < 0) {
    printf("Erro ao configurar interrucao no pino: %d\n", pino);
    return -1;
  }

  if ( wiringPiISR (pino, INT_EDGE_FALLING, &notificar) < 0 ) {
    printf("Erro ao ativar interrucao no pino: %d\n", pino);
    return -1;
  }
  return 1;
}

int monitorarTodosPinos(){
  if(monitoraSensorEntrada(SP_SALA) < 0){
    return -1;
  }
  if(monitoraSensorEntrada(SP_COZINHA) < 0){
    return -1;
  }
  if(monitoraSensorEntrada(SA_PORTA_COZINHA) < 0){
    return -1;
  }
  if(monitoraSensorEntrada(SA_JANELA_COZINHA) < 0){
    return -1;
  }
  if(monitoraSensorEntrada(SA_PORTA_SALA) < 0){
    return -1;
  }
  if(monitoraSensorEntrada(SA_JANELA_SALA) < 0){
    return -1;
  }
  if(monitoraSensorEntrada(SA_JANELA_QUARTO_1)< 0){
    return -1;
  }
  if(monitoraSensorEntrada(SA_JANELA_QUARTO_2)< 0){
    return -1;
  }

  return 1;  

}