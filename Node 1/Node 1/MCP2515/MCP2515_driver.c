/*
 * MCP2515_driver.c
 *
 * Created: 05.10.2022 09:42:56
 *  Author: fjmo
 */ 

#include "../MCP2515/MCP2515_driver.h"
#include "../SPI/SPI_driver.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 4.9152E6

#include <stdio.h>

uint8_t  MCP2515_init(void)
{	
	sei(); // Set Global Interrupt Enable bit
	DDRD &= ~(1 << PD2);
	MCUCR |= (1 << ISC01);
    MCUCR &= ~(1 << ISC00);

	GICR |= ( 1 << INT0 ); // Set external interrupt request 0 Enable	
	
	uint8_t value = 0;
	SPI_MasterInit (); // Initialize SPI
	MCP2515_reset (); // Send reset - command
	


	
	// Self - test
	value = MCP2515_read ( MCP_CANSTAT );
	
	if (( value & MODE_MASK ) != MODE_CONFIG ) {
		printf (" MCP2515 is NOT in configuration mode after reset !\n\r");
		return 1;
	}

	//set length of SJW to 2*TQ and BRP to 2 => TQ = 250 ns
	MCP2515_bit_modify(MCP_CNF1,0b11111111,0x41);

	//set length of phase 1 segment to 6*TQ and PROPSEG to 3 TQ
	MCP2515_bit_modify(MCP_CNF2,0b11111111,0x6A);

	//set length of propagation segment to 2*TQ
	MCP2515_bit_modify(MCP_CNF3,0b00000111,0x02);

	//set all RX-interrupts
	MCP2515_bit_modify(MCP_CANINTE, MCP_RX_INT, MCP_RX_INT);

	//clear interrupt flags RX0
	MCP2515_bit_modify(MCP_CANINTF, MCP_RX0IF, 0);
	
	// enable receive
	MCP2515_bit_modify(MCP_RXB0CTRL, 0b01100000 ,0b01100000 );

	return 0;
}

uint8_t MCP2515_set_mode(uint8_t mode)
{
	uint8_t value = 0;
	
	MCP2515_bit_modify(MCP_CANCTRL,MODE_MASK,mode);
	
	value = MCP2515_read ( MCP_CANSTAT );
	if (( value & MODE_MASK ) != mode ) {
		printf (" mcp2515 is not changed to desired mode !\n\r");
		return 1;
	}

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

	return result;
}

void MCP2515_write(uint8_t address, uint8_t data)
{
	PORTB &= ~(1 << PB4 ); // Select CAN - controller, chip select SPI
	
	SPI_write( MCP_WRITE ); // Send write instruction
	SPI_write(address);		// Send address
	SPI_write(data);		// Send data
	
	PORTB |= (1 << PB4 ); // Deselect CAN - controller,  chip select SPI

}

void MCP2515_request_to_send(uint8_t MCP_RTS_N)
{
	PORTB &= ~(1 << PB4 ); // Select CAN - controller, chip select SPI

	SPI_write(MCP_RTS_N);   //Send RTS - instruction

	PORTB |= (1 << PB4 ); // Deselect CAN - controller,  chip select SPI

}

void MCP2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data)
{
	PORTB &= ~(1 << PB4 ); // Select CAN - controller, chip select SPI

	SPI_write(MCP_BITMOD);   //Send bit modify - instruction
	SPI_write(address);		 //Send Address Byte
	SPI_write(mask);		 //Send Mask Byte
	SPI_write(data);		 //Send Data Byte


	PORTB |= (1 << PB4 ); // Deselect CAN - controller,  chip select SPI
}

void MCP2515_reset(void)
{
	PORTB &= ~(1 << PB4 ); // Select CAN - controller, chip select SPI

	SPI_write(MCP_RESET);   //Send Reset - instruction

	PORTB |= (1 << PB4 ); // Deselect CAN - controller,  chip select SPI
}

uint8_t MCP2515_read_status(void)
{
	uint8_t result;

	PORTB &= ~(1 << PB4 ); // Select CAN - controller, chip select SPI

	SPI_write(MCP_READ_STATUS);   //Send Read status - instruction
	result = SPI_read();		  //Read result 

	PORTB |= (1 << PB4 ); // Deselect CAN - controller,  chip select SPI

	return result;
}
