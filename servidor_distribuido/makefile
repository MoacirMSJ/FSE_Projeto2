start:temp main clear

main:log lcd pid bme280 uart pwm diversos
	gcc -I./lib  main.c ./temp/*.o -o ./obj/bin -lwiringPi -lpthread
	# gcc -I./lib  main.c ./temp/log.o ./temp/lcd.o ./temp/pid.o -o ./obj/bin -lwiringPi

temp:
	mkdir ./temp

log:
	gcc -c ./lib/log.c -o ./temp/log.o

lcd:
	gcc -c ./lib/lcd.c -o ./temp/lcd.o

pid:
	gcc -c ./lib/pid.c -o ./temp/pid.o

bme280:
	gcc -c ./lib/bme280.c -o ./temp/bme280.o

uart: crc
	gcc -c ./lib/uart.c -o ./temp/uart.o

crc:
	gcc -c ./lib/crc16.c -o ./temp/crc.o

pwm:
	gcc -c ./lib/pwm.c -o ./temp/pwm.o

diversos:
	gcc -c ./lib/diversos.c -o ./temp/div.o

clear:
	rm -rf ./temp