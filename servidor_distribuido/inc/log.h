#ifndef LOG_H_
#define LOG_H_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tipos.h"


#define ARQUIVO "./data/logs.csv"
FILE *arq;

void novoRegistro();
void registrarLog(char *requisicao, char comando);
void fecharArquivoLog();


#endif /* LOG_H_ */
