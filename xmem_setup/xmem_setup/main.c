/*
 * xmem_setup.c
 *
 * Created: 07.09.2022 09:02:38
 * Author : akilanj
 */ 

#include <avr/interrupt.h>
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
#include "MCP2515_constants.h"
#include "CANdriver.h"

uint8_t MCP_val_read;


// Interrupt vector for INT0
ISR(INT0_vect)
{
	//printf("___in ISR___ \n\r");
	// user code here
	
	
	volatile uint8_t interrupt_value;
	interrupt_value = MCP2515_read( MCP_CANINTF );
	
	MCP2515_bit_modify(MCP_CANINTF, interrupt_value, 0x00);
	
	printf("Interrupt value: %d \n\r", interrupt_value);
	
	MCP_val_read = CAN_receive();

}


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
		
		uint8_t interrupt_value;		
		uint8_t MCP_val_send; 
		//uint8_t MCP_val_read;
	
		MCP_val_send = 0b10011001; 
		
		printf("___________1____________\n\n\r");
		
		//Transmit Data
		CAN_transmit(0xFF, 0x0F, MCP_val_send);
		
		
		printf("Sent value: %d \n\r", MCP_val_send);
		
		////Read Data
		//MCP_val_read = CAN_receive();
	
		printf("Received value: %d \n\r", MCP_val_read);
		
		
		

		_delay_ms(2000);
		
		printf("___________2____________\n\n\r");
		
		//Transmit Data
		MCP_val_send = 0b10101011;
		
		CAN_transmit(0xFF, 0x0F, MCP_val_send);
		
		////Read Data
		//MCP_val_read = CAN_receive();
		
		printf("Sendt value: %d \n\r", MCP_val_send);
		printf("Received value: %d \n\r", MCP_val_read);
		
		_delay_ms(1000);
		
	}
}
 