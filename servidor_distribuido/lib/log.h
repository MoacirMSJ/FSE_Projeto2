#ifndef LOG_H_
#define LOG_H_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tipos.h"


#define ARQUIVO "./logs.csv"
FILE *arq;

void novoRegistro();
void registrarLog( DadosUart dados, float tExterna, float tUsuario, PidDados pid);
void fecharArquivoLog();


#endif /* LOG_H_ */
