#include "servidor.h"

void encerrarServidor(){
  printf("Encerrando servidor\n");
  close(socketCliente);
  close(socketCliente);
}
void tocarAlarme(){
	while(alarme_ativado){
		system("cd ..; omxplayer alarme.mp3 > /dev/null");
	}
	
  // printf("iiiiuuu iuuuuuu iuuuuu iiuuuuuuu\n");
}

void trataRequisicao(int socketCliente) {
	if(alarme_ativado && !notificacao_recebida){

		char buffer[16] = "notificado";
		int tamanhoRecebido = 11;

  	tocarAlarme();

		while (tamanhoRecebido > 0) {
			if(send(socketCliente, buffer, tamanhoRecebido, 0) != tamanhoRecebido){
				printf("Notificacao alarme: Erro no envio - send()\n");
			}else{
				notificacao_recebida = true;
			}
			if((tamanhoRecebido = recv(socketCliente, buffer, 16, 0)) < 0)
				printf("Erro no recv()\n");
		}
	}
	
}

void servidor() {

	struct sockaddr_in servidorAddr;
	struct sockaddr_in clienteAddr;
	unsigned int clienteLength;

	// Abrir Socket
	if((servidorSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		printf("falha no socker do Servidor\n");

	// Montar a estrutura sockaddr_in
	memset(&servidorAddr, 0, sizeof(servidorAddr)); // Zerando a estrutura de dados
	servidorAddr.sin_family = AF_INET;
	servidorAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servidorAddr.sin_port = htons(PORTA);

	// Bind
	if(bind(servidorSocket, (struct sockaddr *) &servidorAddr, sizeof(servidorAddr)) < 0)
		printf("Falha no Bind\n");

	// Aguarda um mensagem de alarme
	if(listen(servidorSocket, 10) < 0){
		printf("Falha no Listen\n");
  }		

	while(1) {
		clienteLength = sizeof(clienteAddr);
		if((socketCliente = accept(servidorSocket, 
			                      (struct sockaddr *) &clienteAddr, 
			                      &clienteLength)) < 0)
			printf("Falha no Accept\n");
		
		printf("Conexão do Cliente %s\n", inet_ntoa(clienteAddr.sin_addr));
		if(alarme_ativado && !notificacao_recebida){
		  trataRequisicao(socketCliente);
    }
		close(socketCliente);
	}
	close(servidorSocket);

}
