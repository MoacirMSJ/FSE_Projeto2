#include "tcp.h"


void servidor(){
  int servidorSocket, clienteSocket;
  struct sockaddr_in servidorEndereco, clienteEndereco;

  servidorSocket = socket(PF_INET, SOCK_STREAM,IPPROTO_TCP);

  if(servidorSocket < 0){
    printf("Servidor: Falha no socket");
    exit(1);
  }

  memset(&servidorEndereco, 0, sizeof(servidorEndereco)); // Zerando a estrutura de dados
	servidorEndereco.sin_family = AF_INET;
	servidorEndereco.sin_addr.s_addr = htonl(INADDR_ANY);
	servidorEndereco.sin_port = htons(PORTA);





}