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
  printf("pwm: %d %d",RESISTORPWM,VENTOINHAPWM);
  zeraIntensidadePWM(RESISTORPWM, VENTOINHAPWM);
  ClrLcd();
  fecharArquivoUART();
  fecharArquivoLog();
  fecharArquivoI2C();
  exit(1);
}

void mensagemErro(){
  printf("Temperatura invalida,não pode ser menor que a Temperatura externa ou maior que 90 graus.\n");
  printf("Precione enter: \n");
  getchar();
}

void mostrarDados(DadosUart dados, float tExterna, float temperaturaDesejada, PidDados pidAux){
  displayLcd(dados.sensorLM35, tExterna, temperaturaDesejada);
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  printf(" _____________________________________________________\n");
  printf("|             Horario %02d:%02d:%02d                      |\n",tm.tm_hour, tm.tm_min, tm.tm_sec);
  printf("|TI: %.2f |TE: %2.2f |TR: %2.2f |V: %2.2f%% |R: %2.2f%% |\n",dados.sensorLM35, tExterna, temperaturaDesejada, pidAux.ventoinha, pidAux.resistencia);
  printf("|_____________________________________________________|\n");
}