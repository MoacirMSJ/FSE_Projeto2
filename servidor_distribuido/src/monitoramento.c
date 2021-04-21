#include "monitoramento.h"


void notificar(void) {
  clienteMonitoramento("9:Alarme");
}


int monitoraSensorEntrada(int pino) {
  if (wiringPiSetup () < 0) {
    printf("Erro ao configurar interrucao no pino: %d\n", pino);
    return -1;
  }

  if ( wiringPiISR (pino, INT_EDGE_RISING, &notificar) < 0 ) {
    printf("Erro ao ativar interrucao no pino: %d\n", pino);
    return -1;
  }
  return 1;
}

int monitorarTodosPinos(){
  if(monitoraSensorEntrada(SP_SALA) < 0){
    return -1;
  }
  if(monitoraSensorEntrada(SP_COZINHA) < 0){
    return -1;
  }
  if(monitoraSensorEntrada(SA_PORTA_COZINHA) < 0){
    return -1;
  }
  if(monitoraSensorEntrada(SA_JANELA_COZINHA) < 0){
    return -1;
  }
  if(monitoraSensorEntrada(SA_PORTA_SALA) < 0){
    return -1;
  }
  if(monitoraSensorEntrada(SA_JANELA_SALA) < 0){
    return -1;
  }
  if(monitoraSensorEntrada(SA_JANELA_QUARTO_1)< 0){
    return -1;
  }
  if(monitoraSensorEntrada(SA_JANELA_QUARTO_2)< 0){
    return -1;
  }

  return 1;  

}

void clienteMonitoramento(char *mensagem){

	int clienteSocket;
	struct sockaddr_in servidorEndereco;
	char buffer[16];
	unsigned int tamanhoMensagem;

	int bytesRecebidos;
	int totalBytesRecebidos;

	// Criar Socket
	if((clienteSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		printf("Erro no socket()\n");

	// Construir struct sockaddr_in
	memset(&servidorEndereco, 0, sizeof(servidorEndereco)); // Zerando a estrutura de dados
	servidorEndereco.sin_family = AF_INET;
	servidorEndereco.sin_addr.s_addr = inet_addr(SERV_CENTRAL_IP);
	servidorEndereco.sin_port = htons(SERV_CENTRAL_PORTA);

	// Connect
	if(connect(clienteSocket, (struct sockaddr *) &servidorEndereco, 
							sizeof(servidorEndereco)) < 0)
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
		printf("%s\n", buffer);
	}
	close(clienteSocket);

}