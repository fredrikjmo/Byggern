/*
 * MCP2515_driver.c
 *
 * Created: 05.10.2022 09:42:56
 *  Author: fjmo
 */ 

#include "MCP2515_driver.h"
#include "SPI_driver.h"
#include <stdio.h>


uint8_t  MCP2515_init(void)
{
	uint8_t value = 0;
	SPI_MasterInit (); // Initialize SPI
	MCP251_reset (); // Send reset - command
	
	// Self - test
	value = MCP2515_read ( MCP_CANSTAT );
	
	//printf( "value & mask %d", value & MODE_MASK);
	//printf("\n\r");	
	//printf( "mode_config %d", MODE_CONFIG);
	//printf("\n\n\r");
	
	if (( value & MODE_MASK ) != MODE_CONFIG ) {
		printf (" MCP2515 is NOT in configuration mode after reset !\n\r");
		return 1;
		
	}	printf("MCP in Config-mode\n\r");
	
	
	
	
	
	
	
	
	return 0;
}

uint8_t MCP2515_set_mode(uint8_t mode)
{
	uint8_t value = 0;
	
	MCP251_bit_modify(MCP_CANCTRL,MODE_MASK,mode);
	
	value = MCP2515_read ( MCP_CANSTAT );
	if (( value & MODE_MASK ) != mode ) {
		printf (" mcp2515 is not changed to desired mode !\n\r");
		return 1;
		
	}		printf("MCP successfully changed mode\n\r");
	
	return 0;
	
}




uint8_t MCP2515_read(uint8_t address)
{
	uint8_t result ;
	
	PORTB &= ~(1 << PB4 ); // Select CAN - controller, chip select SPI
	
	SPI_write( MCP_READ ); // Send read instruction
	SPI_write( address ); // Send address
	result = SPI_read() ; // Read result
	
	PORTB |= (1 << PB4 ); // Deselect CAN - controller,  chip select SPI
	
	return result ;
	
	
}


void MCP251_write(uint8_t address, uint8_t data)
{
	PORTB &= ~(1 << PB4 ); // Select CAN - controller, chip select SPI
	
	SPI_write( MCP_WRITE ); // Send write instruction
	SPI_write(address);		// Send address
	SPI_write(data);		// Send data
	
	PORTB |= (1 << PB4 ); // Deselect CAN - controller,  chip select SPI
	
	
}

void MCP251_request_to_send(uint8_t MCP_RTS_N)
{
	PORTB &= ~(1 << PB4 ); // Select CAN - controller, chip select SPI
	
	SPI_write(MCP_RTS_N);   //Send RTS - instruction
	
	PORTB |= (1 << PB4 ); // Deselect CAN - controller,  chip select SPI
	
}

void MCP251_bit_modify(uint8_t address, uint8_t mask, uint8_t data)
{
	
	PORTB &= ~(1 << PB4 ); // Select CAN - controller, chip select SPI
	
	SPI_write(MCP_BITMOD);   //Send RTS - instruction
	SPI_write(address);		 //Send Address Byte
	SPI_write(mask);		 //Send Mask Byte
	SPI_write(data);		 //Send Data Byte
	
	
	PORTB |= (1 << PB4 ); // Deselect CAN - controller,  chip select SPI
	
	
}


void MCP251_reset(void)
{
	PORTB &= ~(1 << PB4 ); // Select CAN - controller, chip select SPI
		
	SPI_write(MCP_RESET);   //Send Reset - instruction
		
	PORTB |= (1 << PB4 ); // Deselect CAN - controller,  chip select SPI
	
}

uint8_t MCP251_read_status(void)
{
	
	uint8_t result;
	
	PORTB &= ~(1 << PB4 ); // Select CAN - controller, chip select SPI
		
	SPI_write(MCP_READ_STATUS);   //Send Read status - instruction
	result = SPI_read();		  //Read result 
		
	PORTB |= (1 << PB4 ); // Deselect CAN - controller,  chip select SPI
		
	return result;

}
