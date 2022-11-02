/*
 * motor_controller.h
 *
 * Created: 26.10.2022 16:46:33
 *  Author: akilanj
 */ 


#ifndef MOTOR_CONTROLLER_H_
#define MOTOR_CONTROLLER_H_
#include <stdio.h>
#include "sam.h"

// MJ1 pins
#define DIR			PIO_PER_P10 //PD10
#define EN			PIO_PER_P9   //PD9
#define SEL			PIO_PER_P2   //PD2
#define NOT_RST		PIO_PER_P1   //PD1
#define NOT_IOE		PIO_PER_P0   //PD0

// MJ2 pins
#define DO0			PIO_PER_P1 //PC1
#define DO1			PIO_PER_P2 //PC2
#define DO2			PIO_PER_P3 //PC3
#define DO3			PIO_PER_P4 //PC4
#define DO4			PIO_PER_P5 //PC5
#define DO5			PIO_PER_P6 //PC6
#define DO6			PIO_PER_P7 //PC7
#define DO7			PIO_PER_P8 //PC8

#define DO0_IDX             1

#define MOTOR_TIMER_FREQ    50



void print_joy_h ( void );

void set_joystick_horizontal_val(uint8_t val);
void set_right_slider_val(uint8_t val);
void set_right_button_val(uint8_t val);

void motor_init(void);
void motor_disable_break(uint8_t bool);
void motor_set_speed(uint32_t speed);
void motor_set_direction(uint8_t dir);

void motor_encoder_reset(void);
uint16_t motor_encoder_read(void);

void motor_raw_dog(void);

void DAC_init(void);
void joystick_horizontal_to_speed(uint32_t joystick_output);

#endif /* MOTOR_CONTROLLER_H_ */