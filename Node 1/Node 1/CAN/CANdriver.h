/*
 * CANdriver.h
 *
 * Created: 06.10.2022 11:21:08
 *  Author: akilanj
 */ 


#ifndef CANDRIVER_H_
#define CANDRIVER_H_

#include "../MCP2515/MCP2515_constants.h"
#include "../MCP2515/MCP2515_driver.h"
#include "../ADC/ADCdriver.h"


typedef struct can_message_t
{
	uint16_t id;
	char data_length;
	char data[8];
} CAN_MESSAGE;

void CAN_transmit ( CAN_MESSAGE message );

CAN_MESSAGE CAN_receive ( void );

void CAN_send_joystick_direction (void);

CAN_MESSAGE get_MCP_val_read( void );


#endif /* CANDRIVER_H_ */