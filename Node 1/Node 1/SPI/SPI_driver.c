/*
 * SPI_driver.c
 *
 * Created: 05.10.2022 09:25:56
 *  Author: fjmo
 */ 

#include "SPI_driver.h"


void SPI_MasterInit(void)
{	
	/* Set MOSI, SCK, *SS as output, all others input */
	DDRB |= (1<<DDB5)|(1<<DDB7)|(1<<DDB4);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	//set MISO to input
	DDRB &= ~(1<<DDB6);	
}


void SPI_write(uint8_t data)
{
	/* Start transmission */
	SPDR = data;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
}

uint8_t SPI_read(void)
{
	// Send dummy-byte to receive data
	SPI_write(0xF);
	
	return SPDR;
}
