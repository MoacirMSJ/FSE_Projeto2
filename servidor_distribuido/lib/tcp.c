#include "tcp.h"

#define SUCESSO "Ok"
#define ERROR "Falha"


#define SERV_CENTRAL_PORTA 10026
#define SERV_CENTRAL_IP "192.168.0.53"

union Dados{
	float valor;
	char valor_string[4];
};

void trataRequisicao(int clienteSocket) {
	char buffer[16];
	int tamanhoRecebido;

	if((tamanhoRecebido = recv(clienteSocket, buffer, 10, 0)) < 0)
		printf("Erro no recv()\n");	
	
	switch(buffer[0]){
		int pino = buffer[1] - '0';
		int intencidade = ((buffer[2] - '0') == 0)? 0:1;
		// temperatura e umidade
		case '0':
			Dados temp, umi;
			TempUmidade tempUmidade = valorTemperaturaUmidade();
			temp.valor = tempUmidade.temperatura;
			umi.valor = tempUmidade.umidade;

			strcat(buffer, temp.valor_string);
   		strcat(buffer, umi.valor_string);
			tamanhoRecebido = 8;
			break;

		// Lampadas
		case '1':
			enviarIntensidadePWM(pino,intencidade);
			printf("Lampada intencidade: %d\n",intencidade);
			strcpy(buffer, SUCESSO);
			tamanhoRecebido=3;
			break;
		// Ar-condicionado
		case '2':
			
			enviarIntensidadePWM(pino, intencidade);
			printf("Ar-condicionado intencidade: %d\n",intencidade);
			strcpy(buffer, SUCESSO);
			tamanhoRecebido=3;
			break;
		//Ligar Alarme
		case '3':
			if(verificaSeSensolesEstaoDesligados() != 0){
				printf("Error: Algum sensor de presença está com acionado\n");
				strcpy(buffer, ERROR);
				tamanhoRecebido=6;
			}
			else{
				if(monitorarTodosPinos() < 0){
					printf("Erro ao ativar monitoramento");
					strcpy(buffer, error);
					tamanhoRecebido=6;

				}else{
					printf("Alarme ativado\n");
					strcpy(buffer, SUCESSO);
					tamanhoRecebido=3;
				}
				
			}
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


void cliente(char mensagem){

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
	exit(0);

}