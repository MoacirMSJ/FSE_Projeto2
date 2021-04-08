#ifndef UART_H_
#define UART_H_


#include <stdio.h>
#include <unistd.h>         //Used for UART
#include <fcntl.h>          //Used for UART
#include <termios.h>        //Used for UART
#include <string.h>
#include "crc16.h"
#include <errno.h>
#include "tipos.h"


//ENDERECO
#define ENDERECO 0x01

// CODIGO
#define SOLICITA 0x23

#define FINALMATRICULA 0366

// SUB-CODIGO
  //TIPO
#define TINTERNA 0XC1
#define TPOTENCIOMETRO 0XC2



union CRC {
    short crc;
    unsigned char b[2];
};

unsigned char tx_buffer[9];

unsigned char rx_buffer[9];

void fecharArquivoUART();
void abrirArquivoUART();
void escreverUart(int tm);
float lerValor();
float solicitarDados(unsigned char codigo);
DadosUart solicitarDadosUART();


#endif