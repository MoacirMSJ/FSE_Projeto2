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
  fprintf(arq,"Data, H:M:S, TI, TE, TR, R, V\n");
  fclose(arq);
  aux= -1;
}

// registrarLog(tempo, dados.sensorLM35,tExterna, dados.potenciometro, temperaturaDesejada, modo);

// Data e hora, temperatura interna, temperatura externa, temperatura definida pelo usuário, 
// valor de acionamento dos atuadores (Resistor e Venoinha em valor percentual)).

void registrarLog(DadosUart dados, float tExterna, float tReferencia, PidDados pid){
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);


  arq = fopen(ARQUIVO, "a+");
  if (arq == NULL) {
    printf("Falha ao abrir o arquivo\n");
    return ;
  }
  aux= 1;
  fprintf(arq,"%02d/%02d/%02d, %02d:%02d:%02d, %.2f, %.2f, %.2f, %.2f, %.2f\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, 
          tm.tm_hour, tm.tm_min, tm.tm_sec,
          dados.sensorLM35, tExterna, tReferencia,
          pid.resistencia, pid.ventoinha);

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
