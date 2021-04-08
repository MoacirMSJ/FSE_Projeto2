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
  novoRegistro();
  menu();
  signal(SIGINT,finaliza);
  signal(SIGALRM,alarme); 
  signal(SIGTSTP, abreMenu);
  pid_configura_constantes(Kp,Ki,Kd);
  criarPinosPWM(RESISTORPWM, VENTOINHAPWM);

  system("clear");
  while(1){
    subMenu();
    alarm(1);
    pid_atualiza_referencia(temperaturaDesejada);

    dados = solicitarDadosUART();
    tExterna= bmeTempExterna();
    if(modo == 'p'){
      temperaturaDesejada =  dados.potenciometro;
    }
    verificaTemperaturas(dados, tExterna);
    
    float pid = (float ) pid_controle(dados.sensorLM35);

    if(pid <= -40.0 ){
      //desliga resistenca e ligar ventoinha
      pidAux.ventoinha = pid;
      pidAux.resistencia = 0.0;
      enviarIntensidadePWM(VENTOINHAPWM, (-1)*pid);
      enviarIntensidadePWM(RESISTORPWM, 0);
    }
    else if(pid >=1){
       //desliga ventoinha e liga resistencia.
      pidAux.ventoinha = 0.0;
      pidAux.resistencia = pid;
      enviarIntensidadePWM(RESISTORPWM, pid);
      enviarIntensidadePWM(VENTOINHAPWM, 0);
    }
    else{
      //desliga os 2;
      pidAux.ventoinha = 0.0;
      pidAux.resistencia = 0.0;
      zeraIntensidadePWM(RESISTORPWM, VENTOINHAPWM);
    }
 


    // medirTempo(tempo);
    registrarLog(dados, tExterna, temperaturaDesejada, pidAux);
    mostrarDados(dados, tExterna, temperaturaDesejada, pidAux );
    // printf("Horario %d:%02d:%02d\n",tempo.tm_hora, tempo.tm_min, tempo.tm_seg);
    // printf("TI: %.2f |TE: %.2f |TR: %.2f |V: %.2f%% |R: %.2f%%\n",dados.sensorLM35, tExterna, temperaturaDesejada,abs(pidAux.ventoinha), pidAux.resistencia);

    pause();
    system("clear");
  }

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


