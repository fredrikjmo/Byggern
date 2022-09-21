/*
 * OLEDdriver.h
 *
 * Created: 21.09.2022 17:34:33
 *  Author: akilanj
 */ 

#ifndef OLEDDRIVER_H_
#define OLEDDRIVER_H_

#include "XMEMdriver.h"

#define OLED_COMMAND_BASE_ADDRESS 0x1000
#define OLED_DATA_BASE_ADDRESS 0x1200

void write_c ( uint8_t data );

void oled_init ( void );




#endif /* OLEDDRIVER_H_ */