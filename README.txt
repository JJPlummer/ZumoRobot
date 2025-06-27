You will need:

main.c: 
Write all of your code in this file. 

zumo_drivers.o and zumo_drivers.h: 
You will need these files in your working folder to access functions in the zumo drivers. Refer to the list of functions on watsonwiki.binghamton.edu. Your main file should have the following preprocessor directive at the top. 

#include "zumo_drivers.h"

Also call the function configure_zumo(); in your main loop once at the begining. 

makefile: 
This compiles your program. Enter 'make all' in the command prompt. 
The file calls the zumo_avr_prog batch file. Once you are in bootloader mode (press reset twice), this bat file will look for possible com ports and when finds the correct one, it will program your robot. 

Comment out the first line (see below) when running on a machine other than Applications Pool. 
"export PATH := C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin:$(PATH)"