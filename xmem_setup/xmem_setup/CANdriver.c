/*
 * CANdriver.c
 *
 * Created: 06.10.2022 11:21:19
 *  Author: akilanj
 */ 

#include "CANdriver.h"

void CAN_transmit ( uint8_t IDH, uint8_t IDL, uint8_t data )
{
	// Transmit setup
	MCP2515_write( MCP_TXB0SIDH, IDH );
	MCP2515_write( MCP_TXB0SIDL, IDL );
	MCP2515_write( MCP_TXB0DLC, 1 );
	MCP2515_write( MCP_TXB0D0, data );
	
	// Request-to-send command
	MCP2515_request_to_send(MCP_RTS_TX0);
}

uint8_t CAN_receive ( void )
{
	uint8_t IDH;
	uint8_t IDL;
	uint8_t data_length;
	uint8_t data;
	
	IDH = MCP2515_read(MCP_RXB0SIDH);
	IDL = MCP2515_read(MCP_RXB0SIDL);
	data_length = MCP2515_read(MCP_RXB0DLC);
	data = MCP2515_read(MCP_RXB0D0);
	
	return data;
}