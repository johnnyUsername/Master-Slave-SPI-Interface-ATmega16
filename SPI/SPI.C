/*
	Author: Ivan Kucinic

*/



#include "SPI.h"

// ----FOR MASTER----

// Initializes master of SPI (Device that will send data)
void SPI_InitMaster()
{
	
	DDRB |= (1<<MOSI)|(1<<SCK)|(1<<SS); // Set MOSI, SCK and SS as output
	DDRB &= ~(1<<MISO);	// Set MISO as input		
			
	PORTB |= (1<<SS); // Set SS pin HIGH	
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0); // Set SPE HIGH(enables SPI), MSTR HIGH(enables Master), SPR0 HIGH(for SCK frequency)
	
	// SPI2X=0, SPR1=0, SPR0=1 => SCK frequency is fsc/16					
	SPSR &= ~(1<<SPI2X);
}

// Used for transmitting char data type
void SPI_Transmit(char data)
{
	char flush_buffer; 
	SPDR = data; // Initiating data transmission by writing to SPDR register	
	while(!(SPSR & (1<<SPIF)));	// Waiting for SPIF flag in SPSR register to be set, cause that will mark end of serial transfer
	flush_buffer = SPDR; // Clearing SPDR register
}

// Used for transmitting string characters 
void SPI_TransmitStringChar(char * data)
{
	char flush_buffer;
	SPDR = data; // Initiating data transmission by writing to SPDR register
	while(!(SPSR & (1<<SPIF)));	// Waiting for SPIF flag in SPSR register to be set, cause that will mark end of serial transfer
	flush_buffer = SPDR; // Clearing SPDR register
}

// Used for transmitting uint8_t data type
void SPI_TransmitInt(uint8_t data)
{
	char newData = ((char) data); // Converting from uint8_t to char
	
	char clearBuffer;
	SPDR = data;		// Initiating data transmission by writing to SPDR register	
	while(!(SPSR & (1<<SPIF)));	// Waiting for SPIF flag in SPSR register to be set, cause that will mark end of serial transfer
	clearBuffer = SPDR; // Clearing SPDR register
}

// Used for transmitting string data type
void SPI_TransmitString(char * data)
{	
	char * character;
	int lenght = strlen(data) + 1; // Determining number of characters
	_delay_ms(2000);
	
	for (int i = 0; i < lenght; i++) // Going through string and sending each character individually
	{
		character = (*(data + i)); // Taking character from string data
		
		SPI_TransmitStringChar(character); // Transmitting character
		
		_delay_ms(155);
	}
	
}

// ----FOR SLAVE----

// Used for initializing Slave (device that will receive data)
void SPI_InitSlave()
{
	DDRB &= ~((1<<MOSI)|(1<<SCK)|(1<<SS)); // Set MOSI, SCK and SS pin as input
	
	DDRB |= (1<<MISO); // Set MISO pin as output
	
	SPCR = (1<<SPE); // Enable SPI by setting SPE of SPCR register to HIGH
}

// Used for receiving char data type from serial transmission
char SPI_Receive()
{
	while(!(SPSR & (1<<SPIF))); // Waiting for SPIF flag in SPSR register to be set, cause that will mark end of serial transfer
	
	return SPDR; // Return data register
}

// Used for receiving uint8_t data type from serial transmission
uint8_t SPI_ReceiveInt()
{
	while(!(SPSR & (1<<SPIF))); // Waiting for SPIF flag in SPSR register to be set, cause that will mark end of serial transfer
	
	return SPDR; // Return data register
}

// Used for receiving string data
char * SPI_ReceiveString()
{
	char data[STRING_LENGTH] = "";
	char * newChar;
	bool endTransmission = true;
	
	while(endTransmission)
	{
		newChar = SPI_Receive(); // Receive char
		
		if (newChar == '\0')
		{
			endTransmission = false;
		}
		
		strcat(data, &newChar); // Add received char to existing array
		
		_delay_ms(150);
	}
	
	char * receivedData = data;
	
	return receivedData;
}