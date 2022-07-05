/*
 * SlaveAtmega16.c
 *
 * Used for receiving data over SPI.
 *
 * Author : Ivan Kucinic
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "LCD/lcd.h" // You need to have some kind of library for printing data to LCD display
#include "SPI/SPI.h"

void setup()
{
	SPI_InitSlave();
	lcd_init();
}


int main(void)
{
    setup();
    
    uint8_t receiveInteger = 0;
    char receiveChar;
	char * receiveString;
	
    lcd_clrscr();
    lcd_home();
    lcd_print("Starting...");
    
    _delay_ms(1000);
    
    while (1)
    {
		lcd_clrscr();
		lcd_home();
		lcd_print("Receiving...");
		
	    receiveInteger = SPI_ReceiveInt(); // Uncomment to receive integer
		//receiveChar = SPI_Receive(); // Uncomment to receive char
		//receiveString = SPI_ReceiveString(); // Uncomment to receive string
		
		lcd_clrscr();
		lcd_home();
		lcd_print("Received:");
		lcd_print("%d", receiveInteger); // Uncomment for printing received integer
		//lcd_print("%c", receiveChar); // Uncomment for printing received char
		//lcd_print("%s", receiveString); // Uncomment for printing received string
		
	    _delay_ms(3000);
    }
}

