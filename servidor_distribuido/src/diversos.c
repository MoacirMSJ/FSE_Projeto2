#include "diversos.h"
void alarme(int s){
  alarm(1); 
}

void subMenu(){

  printf("           ___________________________\n");
  printf("          |         ATALHOS           |\n");
  printf("          |Ctr+c: Finalizar execucao. |\n");
  printf("          |Ctr+z: Abrir menu.         |\n");
  printf("          |___________________________|\n");
}

void finaliza(int s){
  printf("Finalizando...\n");
  printf("Desligando aparelhos..\n");
  desligaAparelhos();
  fecharArquivoLog();
  fecharArquivoI2C();
  exit(1);
}

void mensagemErro(){
  printf("Temperatura invalida,não pode ser menor que a Temperatura externa ou maior que 90 graus.\n");
  printf("Precione enter: \n");
  getchar();
}

