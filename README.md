# FSE_Projeto2

## Objetivo

O objetivo deste trabalho é implementar um sistema distribuído,funcionando em conjunto com placas Raspbarry pi, de automação residencial para o monitoramento, acionando sensores e dispositvos. Cada Raspberry executará uma servidor chamdo de central e distribuído.
  
  O **servidor Central** é composto por até dois clientes e um servidor:
   - Um cliente é responsável por solicitar dados de temperatura ao servidor distribuído a cada 1 segundo.
   - O segundo cliente é reponsável por enviar comandos do usuário como acionamento de lampadas, ar-condicionados ou ligar alarme. 
   - O servidor é responsável por aguardar ua mensagem do servidor distribuido quando algum dos sensores de presença ou de abertura mudarem de estado, soando assim um alarme.

  O **servidor Distribuído** é composto por um servidor e pode criar um cliente.
  - Servidor é responsável por receber as mensagens vindas do servidor central e executar o acionamento, leitura de sensore ou criar uma interrupção para monitoramento de sensores de abertura e presença.
  - Cliente é criando quando há um solicitação de alarme onde os sensores de entrada e presença são monitorados. Ao haver uma mudança de estado nesses sensores esse cliente é criado e uma mensagem é enviada ao servidor central.

## Instruções de Uso

1. Clone o projeto em cada Raspbarry:

        git clone https://github.com/MoacirMSJ/FSE_Projeto2.git

2. Entre na pasta.
  
      2.1. Raspbarry que será o servidor distribuído.
      
          cd FSE_Projeto2/servidor_distribuido

      2.2. Raspbarry que será o servidor central.

          cd FSE_Projeto2/servidor_central

3. Compile.

        make

4. Execute(primeiro o servidor distribuido)
    
      4.1. Servidor Distribuido.

        ./obj/bin

      4.2. Servidor Central.

        ./obj/bin

5. No servidor Central as instruções de uso serão apresentadas.

## Autor

**Nome:** Moacir Mascarenha Soares Junior

**Matrícula:** 170080366