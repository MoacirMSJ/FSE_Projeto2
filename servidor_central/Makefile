main: cliente diversos  
	gcc -I./inc  main.c ./obj/*.o -o ./bin/bin  -lpthread
	# gcc -I./lib  main.c ./temp/log.o ./temp/lcd.o ./temp/pid.o -o ./obj/bin -lwiringPi

diversos:
	gcc -I./inc -c ./src/diversos.c -o ./obj/diversos.o

cliente: servidor
	gcc -I./inc -c ./src/cliente.c -o ./obj/cliente.o

servidor:
	gcc -I./inc -c ./src/servidor.c -o ./obj/servidor.o

