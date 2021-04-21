#include "log.h"

int aux = -1;


void novoRegistro(){
  arq = fopen(ARQUIVO, "w");
  if (arq == NULL) {
    printf("Falha ao abrir o arquivo\n");
    return ;
  }
  aux= 1;
  //       TU=temperatura defina pelo usuario, R=resistor, V=ventoinha
  fprintf(arq,"Data, Hora, Aparelho, instrucao, resposta\n");
  fclose(arq);
  aux= -1;
}

// registrarLog(tempo, dados.sensorLM35,tExterna, dados.potenciometro, temperaturaDesejada, modo);

// Data e hora, temperatura interna, temperatura externa, temperatura definida pelo usuário, 
// valor de acionamento dos atuadores (Resistor e Venoinha em valor percentual)).

void registrarLog(char *aparelho ,char comando, char resposta){
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  char com[4], res[6];
  if(comando == '0'){
    strcat(com,"off");
  }
  else{
    strcat(com,"on");
  }
  if(resposta == 'O'){
    strcat(res,"ok");
  }
  else{
    strcat(res,"falha");
  }


  arq = fopen(ARQUIVO, "a+");
  if (arq == NULL) {
    printf("Falha ao abrir o arquivo\n");
    return ;
  }
  aux= 1;
  fprintf(arq,"%02d/%02d/%02d, %02d:%02d:%02d, %s, %s, %s\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, 
          tm.tm_hour, tm.tm_min, tm.tm_sec,
          aparelho, com, res);

  fclose(arq);
  aux= -1;
}


void fecharArquivoLog(){
  if (aux == -1) {
    printf("Arquivo já esta fechado.\n");
    return ;
  }
  fclose(arq);
  printf("fechado arquivo de log...\n");
}