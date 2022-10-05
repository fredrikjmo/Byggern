/*
 * xmem_setup.c
 *
 * Created: 07.09.2022 09:02:38
 * Author : akilanj
 */ 
#include <avr/io.h>
#define F_CPU 4.9152E6

#include <util/delay.h>
#include "XMEMdriver.h"
#include "ADCdriver.h"
#include "USARTdriver.h"
#include "OLEDdriver.h"
#include "mainmenu.h"
#include "SPI_driver.h"
#include "MCP2515_driver.h"


// USART_Init( MYUBRR );

int main(void)
{	
	xmem_init();
	adc_init();
	USART_Init(MYUBRR);
	
	MCP2515_init();
	
	//OLED_init();
	//OLED_clear_screen();
	//mainmenu();
	
	//SPI_MasterInit();
	
	MCP2515_set_mode(MODE_LOOPBACK);
	
	
	while(1)
	{
		//printf("hie");
		//PORTB &= ~(1 << PB4 ); // Select CAN - controller, chip select SPI
		//
		//SPI_write(0b10101010);
		

		
		//SPI_read();
		
		_delay_ms(200);
		
		
		//SPI_read();
		//
		//_delay_ms(200);
		//
		//SPI_write(0xD);
		//
		//_delay_ms(200);
		
		
	}
		
	

}
 