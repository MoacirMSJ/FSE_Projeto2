main:servidor mon i2c gpio 
	gcc -I./inc  main.c ./obj/*.o  -lwiringPi -o ./bin/bin
	# gcc -I./src  main.c ./obj/log.o ./obj/lcd.o ./obj/pid.o -o ./obj/bin -lwiringPi

servidor: diversos log
	gcc -I./inc -c ./src/servidor.c -o ./obj/servidor.o

mon:
	gcc -I./inc -c ./src/monitoramento.c -o ./obj/monitoramento.o


log:
	gcc -I./inc -c ./src/log.c -o ./obj/log.o


i2c:
	gcc -I./inc -c ./src/i2c.c -o ./obj/i2c.o


gpio:
	gcc -I./inc -c ./src/gpio.c -o ./obj/gpio.o

diversos:
	gcc -I./inc -c ./src/diversos.c -o ./obj/div.o
