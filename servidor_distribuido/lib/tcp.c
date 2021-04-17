#include "tcp.h"



void trataRequisicao(int clienteSocket) {
	char buffer[30];
	int tamanhoRecebido;

	if((tamanhoRecebido = recv(clienteSocket, buffer, 16, 0)) < 0)
		printf("Erro no recv()\n");

	
	switch(buffer[0]){
		int pino = buffer[1] - '0';
		int liga = ((buffer[2] - '0') == 0)? 0:1;

		// Lampadas
		case '1':
			// enviarIntensidadePWM(pino,liga);
			printf("Lampada desligdas\n");
			break;
		// Ar-condicionado
		case '2':
			// enviarIntensidadePWM(pino,liga);
			printf("Ar-condicionado ligado\n");
			break;
		default:
			printf("Não reconhecido\n");

	}

	while (tamanhoRecebido > 0) {
		if(send(clienteSocket, buffer, tamanhoRecebido, 0) != tamanhoRecebido)
			printf("Erro no envio - send()\n");
		
		if((tamanhoRecebido = recv(clienteSocket, buffer, tamanhoRecebido, 0)) < 0)
			printf("Erro no recv()\n");
	}
}



void servidor(){
  int servidorSocket, clienteSocket, clienteLength;
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

  if(bind(servidorSocket, (struct sockaddr *) &servidorEndereco, sizeof(servidorEndereco)) < 0){
		printf("Falha no Bind\n");
  }

  if(listen(servidorSocket,5)<0){
    printf("Falha no Listen\n");
  }

  while(1){
    clienteLength = sizeof(clienteEndereco);
		if((clienteSocket = accept(servidorSocket, 
			                      (struct sockaddr *) &clienteEndereco, 
			                      &clienteLength)) < 0)
			printf("Falha no Accept\n");
		
		printf("Conexão do Cliente %s\n", inet_ntoa(clienteEndereco.sin_addr));
		
		trataRequisicao(clienteSocket);
		close(clienteSocket);
  }
  close(servidorSocket);

}