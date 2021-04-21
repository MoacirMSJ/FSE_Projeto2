typedef struct tempo{
  int tm_sec;
  int tm_seg;      
  int tm_min;      
  int tm_hora;     
  int tm_mdia;     
  int tm_mes;      
  int tm_ano;
}Tempo;

typedef struct dadosLog{
  int tm_seg;      
  int tm_min;      
  int tm_hora;     
  int tm_mdia;     
  int tm_mes;      
  int tm_ano;
  float tempInterna;
  float tempExterna;
  float tempDefUsuario;
  float resistorPorcentagem;
  float ventoinhaPorcentagem;

}DadosLog;

typedef struct dadosUart{
  float sensorLM35;
  float potenciometro;
}DadosUart;