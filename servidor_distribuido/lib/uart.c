#include "uart.h"

int uart0_filestream = -1;


void fecharArquivoUART(){
  if(uart0_filestream != -1 ){
    printf("Fechando arquivo...\n");
    close(uart0_filestream);
  }

}

void abrirArquivoUART(){
  uart0_filestream = open("/dev/serial0", O_RDWR | O_NOCTTY | O_NDELAY);      //Open in non blocking read/write mode
  if (uart0_filestream == -1)
  {
      printf("Erro - Não foi possível iniciar a UART.\n");
  }

}

void escreverUart(int tm){
  abrirArquivoUART();
  if (uart0_filestream != -1)
  {
    // printf("Escrevendo caracteres na UART ...");
    int count = write(uart0_filestream, &tx_buffer[0], tm);
    if (count < 0)
    {
        printf("UART TX error\n");
    }
  }
}

float lerValor(){
  float data=-1;
  if (uart0_filestream != -1){
      
    int rx_length = read(uart0_filestream, (void*)rx_buffer, 255);      //Filestream, buffer to store in, number of bytes to read (max)
    int error_n = 0;

    if (rx_length < 0)
    {
      printf("Erro na leitura.\n"); //An error occured (will occur if there are no bytes)
    }
    else if (rx_length == 0)
    {
      printf("Nenhum dado disponível.\n"); //No data waiting
    }
    else
    {
      union CRC crc_recebido, crc_calculado;
      crc_recebido.b[0] = rx_buffer[7];
      crc_recebido.b[1] = rx_buffer[8];
      crc_calculado.crc = calcula_CRC(rx_buffer,7);

      if(crc_recebido.crc != crc_calculado.crc){
        printf("Erro: crc incorreto\n");
        return -1;
      }

      unsigned char aux[4];
      aux[0] = rx_buffer[3];
      aux[1] = rx_buffer[4];
      aux[2] = rx_buffer[5];
      aux[3] = rx_buffer[6];
      memcpy(&data, aux, 4);
    }
  }
  return data;

}

float solicitarDados(unsigned char codigo){
  abrirArquivoUART();

  struct termios options;
  tcgetattr(uart0_filestream, &options);
  options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;     //<Set baud rate
  options.c_iflag = IGNPAR;
  options.c_oflag = 0;
  options.c_lflag = 0;
  tcflush(uart0_filestream, TCIFLUSH);
  tcsetattr(uart0_filestream, TCSANOW, &options);

  union CRC crc_valor;

  tx_buffer[0] = ENDERECO;
  tx_buffer[1] = SOLICITA;

  short int crc;
  unsigned char crc_aux[2];

  tx_buffer[2] = codigo;
  tx_buffer[3] = 0x00;
  tx_buffer[4] = 0x03;
  tx_buffer[5] = 0x06;
  tx_buffer[6] = 0x06;

  crc_valor.crc = calcula_CRC(tx_buffer,7);
  memcpy(&tx_buffer[7],crc_valor.b,2);
  
  escreverUart(9);
  usleep(200000);

  float T = lerValor();

  close(uart0_filestream);
  uart0_filestream = -1;
  return T;
}


DadosUart solicitarDadosUART(){
  DadosUart dados;
  dados.sensorLM35 = solicitarDados(TINTERNA);
  dados.potenciometro = solicitarDados(TPOTENCIOMETRO);
  
  if(dados.sensorLM35 == -1){
    dados.sensorLM35 = solicitarDados(TINTERNA);
  }

  if(dados.potenciometro == -1 ){
    dados.potenciometro = solicitarDados(TPOTENCIOMETRO);
  }

  return dados;
}






