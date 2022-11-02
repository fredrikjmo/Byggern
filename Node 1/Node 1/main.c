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
#include "Interface/Interface.h"

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
		uint8_t joy = adc_direction_read();

		adc_calibrate();
		
		interface_send_MFB_data_to_CAN();
		
		_delay_ms(200);
		
	}
}
 