#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SERVIDOR_PORTA 10126
#define SERVIDOR_IP "127.0.0.1"

void subMenu(){
  printf(" ___________________________\n");
  printf("|         ATALHOS           |\n");
  printf("|Ctr+c: Finalizar execucao. |\n");
  printf("|Ctr+z: Abrir menu.         |\n");
  printf("|___________________________|\n");
}

int mostrarTempUm = 1;


typedef union{
	float valor;
	char valor_string[4];
}Dados;

void bloqueiaImpressaoTempUmidade(){
  mostrarTempUm =0;
}
void desbloqueiaImpressaoTempUmidade(){
  mostrarTempUm =1;
}


void imprimeTemperaturaUmidade(char *tempUmi){
  if(mostrarTempUm == 1 ){
    system("clear");
    
    char temp[5], umi[5];
    temp[0] = tempUmi[0];
    temp[1] = tempUmi[1];
    temp[2] = tempUmi[2];
    temp[3] = tempUmi[3];
    temp[4] = '\0';

    umi[0] = tempUmi[4];
    umi[1] = tempUmi[5];
    umi[2] = tempUmi[6];
    umi[3] = tempUmi[7];
    umi[4] = '\0';
    
    subMenu();
    printf(" Temperatura: %s\n",temp);
    printf(" Umidade: %s%%\n",umi);
  }
}

void cliente(char *mens, int clienteUsuario) {
	int clienteSocket;
	struct sockaddr_in servidorAddr;
	char *mensagem;
	char buffer[16];
	unsigned int tamanhoMensagem;

	int bytesRecebidos;
	int totalBytesRecebidos;

	mensagem = mens;

  // Criar Socket
  if((clienteSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    printf("Erro no socket()\n");

  // Construir struct sockaddr_in
  memset(&servidorAddr, 0, sizeof(servidorAddr)); // Zerando a estrutura de dados
  servidorAddr.sin_family = AF_INET;
  servidorAddr.sin_addr.s_addr = inet_addr(SERVIDOR_IP);
  servidorAddr.sin_port = htons(SERVIDOR_PORTA);
  // Connect
  if(connect(clienteSocket, (struct sockaddr *) &servidorAddr, 
              sizeof(servidorAddr)) < 0)
    printf("Erro no connect()\n");

  tamanhoMensagem = strlen(mensagem);

  if(send(clienteSocket, mensagem, tamanhoMensagem, 0) != tamanhoMensagem)
    printf("Erro no envio: numero de bytes enviados diferente do esperado\n");

  totalBytesRecebidos = 0;
  while(totalBytesRecebidos < tamanhoMensagem) {
    if((bytesRecebidos = recv(clienteSocket, buffer, 16-1, 0)) <= 0)
      printf("Não recebeu o total de bytes enviados\n");
    totalBytesRecebidos += bytesRecebidos;
    buffer[bytesRecebidos] = '\0';
    if(clienteUsuario !=1){
      imprimeTemperaturaUmidade(buffer);
    
    }
    else{
      printf("%s\n", buffer);
      break;
    }
    
  }
  close(clienteSocket);
  
}
