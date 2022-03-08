/*
 * Master_ATmega16.c
 *
 * Created: 28.11.21. 17:05:55
 * Author : Ivan Kucinic
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "SPI/SPI.h"
#include "LCD/lcd.h" // You need to have some kind of library for printing data to display!


void setup()
{
	SPI_InitMaster();
	lcd_init();
}

int main(void)
{
	setup();	
	
	char charData = 'A';
	uint8_t intData = 0;
	char * stringData = "ABCDo";
	//char endChar = '\0';
    
	SS_Enable;
	
	_delay_ms(1500);
	
    while (1) 
    {
		lcd_clrscr();
		lcd_home();
		lcd_print("Sending...");
		
		_delay_ms(1000);
		
		//SPI_TransmitInt(intData); // Transmitting integer (Slave also needs to receive integer!!!)
		//SPI_Transmit(charData); // Transmitting char (Slave also needs to receive char!!!)
		SPI_TransmitString(stringData); // Transmitting string (Slave also needs to receive string!!!)
		
		lcd_clrscr();
		lcd_home();
		lcd_print("Sent:");
		//lcd_print("%d", intData); // Uncomment for printing integer
		//lcd_print("%c", charData); // Uncomment for printing char
		lcd_print("%s", stringData); // Uncomment for printing string
		
		//intData = intData + 1; // Uncomment when sending integer
		//charData = charData + 1; // Uncomment when sending char
		
		_delay_ms(4000);
    }
}

