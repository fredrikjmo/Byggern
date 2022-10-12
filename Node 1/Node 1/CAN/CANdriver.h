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

void CAN_transmit ( uint8_t IDH, uint8_t IDL, uint8_t data );

uint8_t CAN_receive ( void );

#endif /* CANDRIVER_H_ */