/*
 * timer.h
 *
 * Created: 28.10.2022 14:45:31
 *  Author: fjmo
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

void timer_init( void );

void delay_ms( int delay );

void delay_us( int delay );


#endif /* TIMER_H_ */