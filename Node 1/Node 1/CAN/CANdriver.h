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


void CAN_transmit ( uint8_t IDH, uint8_t IDL, uint8_t data1, uint8_t data2, uint8_t data3 );

uint8_t CAN_receive ( void );

void CAN_send_joystick_direction (void);


#endif /* CANDRIVER_H_ */