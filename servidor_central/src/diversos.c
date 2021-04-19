#include "diversos.h"

char aparelhos_status[6] ={'0','0','0','0','0','0'};


void tempo()
{
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  printf("now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

void mostrarStatus(){
  system("clear");
  printf("\t\tAPARELHOS\n");
  printf(" ________________LAMPADAS_____________________\n");
  printf("|COZINHA: %c",aparelhos_status[0]);
  printf("| SALA: %c",aparelhos_status[1]);
  printf("| QUARTO 01: %c",aparelhos_status[2]);
  printf("| QUARTO 02: %c |\n",aparelhos_status[3]);
  printf("|_____________________________________________|\n");  
  printf(" ___________AR-CONDICIONADOS__________\n");
  printf("| QUARTO 01: %c",aparelhos_status[4]);
  printf("| QUARTO 02: %c |\n",aparelhos_status[5]);
  printf("|______________________________________|\n");

  printf("_______ALARME______\n");
  printf(" LIGADO: %d\n",alarme_ativado);
  printf("___________________\n");
}




Entrada subMenuLampada(){
  mostrarStatus();
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
  system("clear");
  switch (opcao)
  {
  int opcao2;
  case 1:
    //endereco da lampada
    // entrada.nome_aparelho[20] = "Cozinha\0";
    entrada.posicao_vetor = 0;
    strcat(entrada.nome_aparelho,"L-Cozinha");
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
    entrada.posicao_vetor = 1;
    strcat(entrada.nome_aparelho,"L-Sala");
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
    entrada.posicao_vetor = 2;
    strcat(entrada.nome_aparelho,"L-Quarto 01");
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
    entrada.posicao_vetor = 3;
    strcat(entrada.nome_aparelho,"L-Quarto 02");
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
    // entrada.nome_aparelho[0]= "";
     strcat(entrada.nome_aparelho,"Invalido");
    return entrada;
    break;
  }

}

Entrada subMenuAr(){
  mostrarStatus();
  Entrada entrada;
  int opcao;
  // entrada.nome_aparelho[20] = "Ar-Condicionado\0";
  entrada.instrucao[0] = '2';
  printf("\nAparelhos de Ar-Condicionado:\n");
  printf("1-Quarto 01\n");
  printf("2-Quarto 02\n");
  printf("Escolha: ");
  scanf("%d",&opcao);
  system("clear");
  switch (opcao)
  {
  int opcao2;
  case 1:
    //endereco da lampada
    entrada.posicao_vetor = 4;
    strcat(entrada.nome_aparelho,"A-Quarto 01");
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
    entrada.posicao_vetor = 5;
    strcat(entrada.nome_aparelho,"A-Quarto 02");
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
     strcat(entrada.nome_aparelho,"Invalido");
    return entrada;
    break;
  }

}

void* enviaComando(void *entrada){
  Entrada *ent = (Entrada *) entrada;
  char response = cliente(ent->instrucao,1);
  if(response == 'O'){
    if(ent->nome_aparelho[0] == 'L' || ent->nome_aparelho[0] == 'A' ){
      aparelhos_status[ent->posicao_vetor] = ent->instrucao[2];
    }
  }

  registrarLog(ent->nome_aparelho, ent->instrucao[2], response);
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


void finaliza(int s){
  printf("Finalizando...\n");
  fecharArquivoLog();
  exit(1);
}


int menu(){
  mostrarStatus();
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



void * solicitaTempUmidade(void *test){
  while(1){
    cliente("0000",0);
    usleep(1000000);
  }
  
}

// void  *solicitacaoUsuario(void *teste){
  
//   system("clear");
//   printf("Slicita Lampada: \n");
//   cliente("1510",1);
//   sleep(2);
//   desbloqueiaImpressaoTempUmidade();
  
// }

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

