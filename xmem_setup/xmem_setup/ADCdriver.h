/*
 * ADCdriver.h
 *
 * Created: 21.09.2022 17:27:19
 *  Author: akilanj
 */ 


#ifndef ADCDRIVER_H_
#define ADCDRIVER_H_

#include "XMEMdriver.h"
#define F_CPU 4.9152E6
#include <util/delay.h>

extern uint8_t m_max_x_value;
extern uint8_t m_min_x_value;
extern uint8_t m_middle_x_value;

extern uint8_t m_max_y_value;
extern uint8_t m_min_y_value;
extern uint8_t m_middle_y_value;

typedef enum direction{
	right,
	left,
	up,
	down,
	neutral}direction;

typedef struct pos_p{
	int8_t x_axis;
	int8_t y_axis;
}pos_p ;

void adc_init ( void );

void adc_sample( void );

void adc_calibrate( void );

uint8_t adc_read ( uint8_t channel );

pos_p pos_read(void);uint8_t pos_left_slider(void);uint8_t pos_right_slider(void);direction direction_read (void);


#endif /* ADCDRIVER_H_ */