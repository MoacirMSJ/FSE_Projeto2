#ifndef LOG_H_
#define LOG_H_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>



#define ARQUIVO "./data/logs.csv"
FILE *arq;

void novoRegistro();
void registrarLog(char *aparelho ,char comando, char resposta);
void fecharArquivoLog();


#endif /* LOG_H_ */