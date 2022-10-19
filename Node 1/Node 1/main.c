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


#include "XMEM/XMEMdriver.h"
#include "ADC/ADCdriver.h"
#include "USART/USARTdriver.h"
#include "OLED/OLEDdriver.h"
#include "menu/mainmenu.h"
#include "MCP2515/MCP2515_constants.h"
#include "MCP2515/MCP2515_driver.h"
#include "SPI/SPI_driver.h"
#include "CAN/CANdriver.h"

uint8_t MCP_val_read;


// Interrupt vector for INT0
ISR(INT0_vect)
{
	//printf("___in ISR___ \n\r");
	// user code here
	
	
	volatile uint8_t interrupt_value;
	interrupt_value = MCP2515_read( MCP_CANINTF );
	
	MCP2515_bit_modify(MCP_CANINTF, interrupt_value, 0x00);
	
	//printf("Interrupt value: %d \n\r", interrupt_value);
	
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
	
	MCP2515_set_mode(MODE_NORMAL);
	
	
	while(1)
	{	
		adc_calibrate();
		uint8_t interrupt_value;		
		uint8_t MCP_val_send; 
		//uint8_t MCP_val_read;
	
		MCP_val_send = 0b10011101; 
		
		//printf("___________1____________\n\n\r");
		////Transmit Data
		//CAN_transmit(0xFF, 0x0F, MCP_val_send);
		//printf("Sent value: %d \n\r", MCP_val_send);
		
		
		direction dir = direction_read();
		printf("Sent joystick dir: %d \n\r", dir);
	
		can_send_direction();
	
		
		_delay_ms(200);
		
	}
}
 