#include <time.h>
#include "servidor.h"
#define SUCESSO "Ok"
#define ERROR "Falha"



typedef union {
	float valor;
	unsigned char valor_string[4];
}Dados;

void trataRequisicao(int clienteSocket) {
	printf("Chegou\n");
	char buffer[16];
	int tamanhoRecebido;

	if((tamanhoRecebido = recv(clienteSocket, buffer, 5, 0)) < 0)
		printf("Erro no recv()\n");	
	
	int pino = buffer[1] - '0';
	int intencidade = ((buffer[2] - '0') == 0)? 0:1;
	printf("------------------------------------\n");
	time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  printf("%d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	switch(buffer[0]){
		// temperatura e umidade
		case '0': ;
			printf("Temperatura\n");
			// Dados temp, umi;
			TempUmidade tempUmidade = valorTemperaturaUmidade();
			float temp = 0;
			float umi = 0;
			temp = tempUmidade.temperatura;
			umi = tempUmidade.umidade;
			
			// printf("temp: %f\n", temp);
			char teste[4];
			sprintf(teste, "%.3f", temp);
			memcpy(buffer, teste,4);
			sprintf(teste, "%.3f", umi);
   		memcpy(&buffer[4], teste,4);
			tamanhoRecebido = 8;
			break;

		// Lampadas
		case '1': ;
			// enviarIntensidadePWM(pino,intencidade);
			printf("Lampada endreco %d intencidade: %d\n",pino,intencidade);
			strcpy(buffer, SUCESSO);
			tamanhoRecebido=3;
			break;
		// Ar-condicionado
		case '2': ;
			if(buffer[1] == 'A'){
				pino = 23;
			}
			else{
				pino = 24;
			}
			// enviarIntensidadePWM(pino, intencidade);
			printf("Endereco ar: %d\n",pino);
			printf("Ar-condicionado intencidade: %d\n",intencidade);
			strcpy(buffer, SUCESSO);
			tamanhoRecebido=3;
			break;
		//Ligar Alarme
		case '3': ;
			printf("Alarme ligando/desligando\n");
			if(verificaSeSensolesEstaoDesligados() != 0){
				printf("Error: Algum sensor de presenca está com acionado\n");
				strcpy(buffer, ERROR);
				tamanhoRecebido=6;
			}
			else{
				if(monitorarTodosPinos() < 0){
					printf("Erro ao ativar monitoramento");
					strcpy(buffer, ERROR);
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
	printf("Tamanho recebido: %d\n", tamanhoRecebido);
	while (tamanhoRecebido > 0) {
		if(send(clienteSocket, buffer, tamanhoRecebido, 0) != tamanhoRecebido)
			printf("Erro no envio - send()\n");
		
		if((tamanhoRecebido = recv(clienteSocket, buffer, tamanhoRecebido, 0)) < 0)
			printf("Erro no recv()\n");
	}
}




void servidor(){
  int clienteLength;
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


