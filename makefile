export PATH := C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin:$(PATH)

F_CPU = 16000000
MCU = atmega32u4
CCOPTS= -g -Wall -Os -std=c99
default: compile

all: program

compile: main.c  
	avr-gcc $(CCOPTS) -mmcu=$(MCU) -DF_CPU=$(F_CPU) -o main main.c zumo_drivers.o
	    
main.hex: compile
	avr-strip main
	avr-objcopy -R .eeprom -O ihex main main.hex

program: main.hex
	#avrdude -p m32u4 -c avrisp2 -P COM3 -U flash:w:main.hex
	.\zumo_avr_prog.bat -f main.hex

clean:
	rm main main.hex


