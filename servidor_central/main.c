#include <stdio.h>
#include <pthread.h>
#include "cliente.h"
#include <signal.h>
#include "servidor.h"


pthread_t auxiliar;
int lampadas[4];
int ar_condicionados[2];





Entrada subMenuLampada(){
  Entrada entrada;
  int opcao;
  entrada.instrucao[0] = '1';
  printf("\nLampadas \n");
  printf("1-Cozinha\n");
  printf("2-Sala\n");
  printf("3-Quarto 01\n");
  printf("4-Quarto 02\n");
  printf("Escolha: ");
  scanf("%d",&opcao);

  switch (opcao)
  {
  int opcao2;
  case 1:
    //endereco da lampada
    // entrada.nome_aparelho[20] = "Cozinha\0";
    strcat(entrada.nome_aparelho,"Cozinha");
    entrada.instrucao[1] = '0';
    printf("Cozinha");
    printf("\n0-Desligar\n");
    printf("1-Ligar\n");
    printf("Escolha: ");
    scanf("%d",&opcao2);
    if(opcao2 == 0){
      entrada.instrucao[2] = '0';
    }else{
      entrada.instrucao[2] = '1';
    }
    return entrada;
    break;  
  case 2:
    // entrada.nome_aparelho[20] = "Sala\0";
    strcat(entrada.nome_aparelho,"Sala");
    entrada.instrucao[1] = '1';
    printf("Sala");
    printf("\n0-Desligar\n");
    printf("1-Ligar\n");
    printf("Escolha: ");
    scanf("%d",&opcao2);
    if(opcao2 == 0){
      entrada.instrucao[2] = '0';
    }else{
      entrada.instrucao[2] = '1';
    }
    return entrada;
    break;
  case 3:
    // entrada.nome_aparelho[20] = "Quarto 01\0";
    strcat(entrada.nome_aparelho,"Quarto 01");
    entrada.instrucao[1] = '2';
    printf("Quarto 01");
    printf("\n0-Desligar\n");
    printf("1-Ligar\n");
    printf("Escolha: ");
    scanf("%d",&opcao2);
    if(opcao2 == 0){
      entrada.instrucao[2] = '0';
    }else{
      entrada.instrucao[2] = '1';
    }
    return entrada;
    break;
  case 4:
    strcat(entrada.nome_aparelho,"Quarto 02");
    // entrada.nome_aparelho[20] = "Quarto 02\0";
    entrada.instrucao[1] = '3';
    printf("Quarto 02");
    printf("\n0-Desligar\n");
    printf("1-Ligar\n");
    printf("Escolha: ");
    scanf("%d",&opcao2);
    if(opcao2 == 0){
      entrada.instrucao[2] = '0';
    }else{
      entrada.instrucao[2] = '1';
    }
    return entrada;
    break;
  
  default:
    entrada.nome_aparelho[0]= "";
    return entrada;
    break;
  }

}

Entrada subMenuAr(){
  Entrada entrada;
  int opcao;
  // entrada.nome_aparelho[20] = "Ar-Condicionado\0";
  entrada.instrucao[0] = '2';
  printf("\nAparelhos de Ar-Condicionado:\n");
  printf("1-Quarto 01\n");
  printf("2-Quarto 02\n");
  printf("Escolha: ");
  scanf("%d",&opcao);
  switch (opcao)
  {
  int opcao2;
  case 1:
    //endereco da lampada
    strcat(entrada.nome_aparelho,"Quarto 01");
    entrada.instrucao[1] = 'A';
    printf("Quarto 01");
    printf("\n0-Desligar\n");
    printf("1-Ligar\n");
    printf("Escolha: ");
    scanf("%d",&opcao2);
    if(opcao2 == 0){
      entrada.instrucao[2] = '0';
    }else{
      entrada.instrucao[2] = '1';
    }
    return entrada;
    break;  
  case 2:
    strcat(entrada.nome_aparelho,"Quarto 02");
    entrada.instrucao[1] = 'a';
    printf("Quarto 02");
    printf("\n0-Desligar\n");
    printf("1-Ligar\n");
    printf("Escolha: ");
    scanf("%d",&opcao2);
    if(opcao2 == 0){
      entrada.instrucao[2] = '0';
    }else{
      entrada.instrucao[2] = '1';
    }
    return entrada;
    break; 
  default:
    entrada.nome_aparelho[0]= "";
    return entrada;
    break;
  }

}

void* enviaComando(void *entrada){
  Entrada *ent = (Entrada *) entrada;
  cliente(ent->instrucao,1);
}



void gerenciaAlarme(){
  tocarAlarme();
  if(alarme_ativado){
    printf("Desligando alarme\n");
    alarme_ativado = false;
    notificacao_recebida = false;
  }
  else{
    printf("Ligando alarme\n");
    pthread_t threadAlarme;  
    Entrada alarmeAux;
    strcat(alarmeAux.nome_aparelho,"Alarme");
    alarmeAux.instrucao[0]='3';
    alarmeAux.instrucao[1]='3';
    pthread_create(&threadAlarme, NULL, enviaComando,&alarmeAux);  
    alarme_ativado = true;
    notificacao_recebida = false;
  }
}





int menu(){
  system("clear");
  int opcao;
  printf("\t\t\t\tMENU\n");
  printf("Opcoes: \n");
  printf("1-Lampadas\n");
  printf("2-Ar-condicionado\n");
  printf("3-Ativar/Desativar Alarme\n");
  printf("5-Encerrar programa\n");
  printf("Escolha: \n");
  scanf("%d",&opcao);

  switch (opcao)
  {
  case 1: ;
    Entrada lampada = subMenuLampada();
    printf("Lampada %s:",lampada.nome_aparelho);
    pthread_create(&auxiliar, NULL, enviaComando,&lampada);
    pthread_join(auxiliar,NULL);
    // clienteUsuario(lampada);
    break;
  case 2: ;
    Entrada ar = subMenuAr();
    printf("Ar-condicionado %s:",ar.nome_aparelho);
    pthread_create(&auxiliar, NULL, enviaComando,&ar);
    pthread_join(auxiliar,NULL);
    // clienteUsuario(ar);
    break;
  case 3: ;
    //Ligar alarme
    gerenciaAlarme();
    break;
  default:
    printf("Encerrando programa\n");
    finaliza(1);
  
    break;
  }

}

pthread_t teste;

pthread_mutex_t chave;

void * rodaloop(void *test){
  while(1){
    cliente("0000",0);
    usleep(1000000);
  }
  
}



void  *solicitacaoUsuario(void *teste){
  
  system("clear");
  printf("Slicita Lampada: \n");
  cliente("1510",1);
  sleep(2);
  desbloqueiaImpressaoTempUmidade();
  
}
void finaliza(int s){
  printf("Finalizando...\n");
  // printf("pwm: %d %d",RESISTORPWM,VENTOINHAPWM);
  // zeraIntensidadePWM(RESISTORPWM, VENTOINHAPWM);
  // ClrLcd();
  // fecharArquivoUART();
  // fecharArquivoLog();
  // fecharArquivoI2C();
  exit(1);
}
void abreMenu(){
  bloqueiaImpressaoTempUmidade();
  menu();
  printf("Precione ENTER para continuar..\n");
  getchar();
  getchar();
  desbloqueiaImpressaoTempUmidade();
}

void* monitoramento(void *s){
  printf("Iniciando monitoramento\n");
  servidor();
}

pthread_t threadMonitoramento;
int main(){

  signal(SIGINT,finaliza); 
  signal(SIGTSTP, abreMenu);
  pthread_create(&teste, NULL,rodaloop,NULL);
  pthread_create(&threadMonitoramento, NULL,monitoramento,NULL);

  pthread_join(teste,NULL);
  pthread_join(threadMonitoramento,NULL);

  return 0;
}