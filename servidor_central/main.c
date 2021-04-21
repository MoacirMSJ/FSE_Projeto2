#include <stdio.h>
#include "diversos.h"
#include "log.h"


int main(){
  novoRegistro();
  signal(SIGINT,finaliza); 
  signal(SIGTSTP, abreMenu);
  pthread_create(&teste, NULL,solicitaTempUmidade,NULL);
  pthread_create(&threadMonitoramento, NULL,monitoramento,NULL);

  pthread_join(teste,NULL);
  pthread_join(threadMonitoramento,NULL);

  return 0;
}