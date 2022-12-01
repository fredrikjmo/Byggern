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




int main(void)
{	
	xmem_init();
	adc_init();
	
	MCP2515_init();
	MCP2515_set_mode(MODE_NORMAL);

	OLED_init();
	OLED_clear_screen();
	mainmenu();
}
 