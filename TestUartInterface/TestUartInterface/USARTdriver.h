#ifndef USARTDRIVER_H
#define USARTDRIVER_H

#include <avr/io.h>

#define FOSC 4.9152E6 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

// Init function for USART
void USART_Init( unsigned int ubrr );

// Transmit function for USART
void USART_Transmit( unsigned char data );

// Receive function for USART
unsigned char USART_Receive( void );

#endif /* UARTDRIVER_H */