#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include "log.h"
#include "bme280.h"
#include "uart.h"
#include "pid.h"
#include "pwm.h"
#include "tipos.h"
#include "diversos.h"
#include "tcp.h"

#define Kp 5.0
#define Ki 1.0
#define Kd 5.0




DadosUart dados;

float temperaturaDesejada;
char modo;
float tExterna;
// DadosLog log;

Tempo tempo;

PidDados pidAux;
float tUsuario = 0;

void menu();
void abreMenu();
void verificaTemperaturas(DadosUart dados, float tExterna);

int main(){
  servidor();
  return 0;
}



void verificaTemperaturas(DadosUart dados, float tExterna){
  for(int i =0; i<3; i++){
    if(dados.sensorLM35 < tExterna || dados.potenciometro < tExterna  ){
      dados = solicitarDadosUART();
    }
    else{
      break;
    }
  }
}

void menu(){
  while(1){
    dados = solicitarDadosUART();
    system("clear");

    tExterna = bmeTempExterna();
    verificaTemperaturas(dados, tExterna);
    printf(" ___________________________________________________________________________\n");
    printf("|                                Menu                                       |\n");
    printf("|Temperatura: Interna = %.2f | Externa = %.2f | Potenciometro = %.2f        |\n", dados.sensorLM35, tExterna ,dados.potenciometro);
    printf("|Opcoes:                                                                    |\n");
    printf("| 1- Definir Temperatura                                                    |\n");
    printf("| 2- Usar potenciometro                                                     |\n");
    printf("| 3- Sair                                                                   |\n");
    printf("|___________________________________________________________________________|\n");
    int opt;
    printf("Digite: ");
    scanf("%d",&opt);
    
    if(opt == 1){

      float tReferencia;
      printf("Insira a temperatura: ");
      scanf("%f",&tReferencia);
      getchar();

      if(tReferencia < tExterna || tReferencia > 90){
        void mensagemErro();
      }else{
        temperaturaDesejada = tReferencia;
        modo ='u';
        tUsuario = temperaturaDesejada;
        break;
      }
    
    }
    else if(opt == 2){
      
      printf("Potenciometro: %.2f\n", dados.potenciometro);
      
      if(dados.potenciometro < tExterna || dados.potenciometro > 90){
        void mensagemErro();
      
      }else{
        temperaturaDesejada = dados.potenciometro;
        modo ='p';
        break;
      }
    }
    else if(opt == 3){
      printf("Finalizando...\n");
      finaliza(1);
      exit(0);
    }
    else{
        printf("Valor invalado\n");
        printf("Precione enter: \n");
        getchar();
    }

  }

}


void abreMenu(){
  menu();
}


