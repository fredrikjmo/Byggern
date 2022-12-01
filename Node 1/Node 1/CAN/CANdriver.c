/*
 * CANdriver.c
 *
 * Created: 06.10.2022 11:21:19
 *  Author: akilanj
 */ 

#include "CANdriver.h"


CAN_MESSAGE MCP_val_read;

// Interrupt vector for INT0
ISR(INT0_vect)
{
	volatile uint8_t interrupt_value;
	interrupt_value = MCP2515_read( MCP_CANINTF );
	MCP_val_read = CAN_receive();
	MCP2515_bit_modify(MCP_CANINTF, MCP_RX0IF, 0);
}

CAN_MESSAGE get_MCP_val_read( void ) {return MCP_val_read;}

void CAN_transmit ( CAN_MESSAGE message )
{
	uint8_t IDH = (uint8_t)(message.id >> 8);
	uint8_t IDL = (uint8_t)(0xFF & message.id);

	// Transmit setup
	MCP2515_write( MCP_TXB0SIDH, IDH );
	MCP2515_write( MCP_TXB0SIDL, IDL );
	MCP2515_write( MCP_TXB0DLC, message.data_length );

	for (uint8_t i = 0; i < message.data_length; i++)
	{
		MCP2515_write( MCP_TXB0D0 + i, message.data[i] );
	}
	
	// Request-to-send command
	MCP2515_request_to_send(MCP_RTS_TX0);
}

CAN_MESSAGE CAN_receive ( void )
{
	CAN_MESSAGE message;
	
	uint8_t IDH = MCP2515_read(MCP_RXB0SIDH);
	uint8_t IDL = MCP2515_read(MCP_RXB0SIDL);

	message.id = (IDH << 8) & IDL;

	message.data_length = MCP2515_read(MCP_RXB0DLC);

	for (uint8_t i = 0; i < message.data_length; i++)
	{
		message.data[i] = MCP2515_read(MCP_RXB0D0 + i);
	}

	//clear interrupt flags RX0
	MCP2515_bit_modify(MCP_CANINTF, MCP_RX0IF, 0);
	
	return message;
}

void CAN_send_joystick_direction (void){
	
	direction joystick_dir = adc_direction_read();
	
	CAN_MESSAGE message;
	message.id = 0xFF0F;
	message.data_length = 1;
	message.data[0] = joystick_dir;

	CAN_transmit(message);
}
