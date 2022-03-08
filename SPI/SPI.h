/*
 * SPI.h
 *
 * This library is used for sending data over
 * SPI/Three wire interface 
 *
 * TESTED ON ATmega16
 *
 * ATmega16 Fuse bits:
 * LOW FUSE: E4
 * HIGH FUSE: D9
 * LOCK FUSE: FF
 *
 * Created: 08.03.2022.
 * Author: Ivan Kucinic
 */ 


#ifndef SPI_H_
#define SPI_H_

#define F_CPU 8000000ul
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdbool.h>

// Default pins for ATmega16
#define SS 4 // Pin number for SS
#define MOSI 5 // Pin number for MOSI
#define MISO 6 // Pin number for MISO
#define SCK 7 // Pin number for SCK

#define SS_Enable PORTB &= ~(1<<SS)	// Function for enabling SS pin (SS pin will be LOW)		
#define SS_Disable PORTB |= (1<<SS) // Function for disabling SS pin (SS pin will be HIGH)

#define STRING_LENGTH 10 // Max number of string characters to receive

// For Master
void SPI_InitMaster();
void SPI_InitSlave();
void SPI_Transmit(char data);
void SPI_TransmitStringChar(char * data);
void SPI_TransmitInt(uint8_t data);
void SPI_TransmitString(char * data);

// For Slave
void SPI_InitSlave();
char SPI_Receive();
uint8_t SPI_ReceiveInt();
char* SPI_ReceiveString();



#endif /* SPI_H_ */