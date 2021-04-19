main:cliente  
	gcc -I./inc  main.c ./obj/*.o -o ./bin/bin  -lpthread
	# gcc -I./lib  main.c ./temp/log.o ./temp/lcd.o ./temp/pid.o -o ./obj/bin -lwiringPi

cliente: servidor
	gcc -I./inc -c ./src/cliente.c -o ./obj/cliente.o

servidor:
	gcc -I./inc -c ./src/servidor.c -o ./obj/servidor.o

