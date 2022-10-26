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

void motor_init(void);
void motor_disable_break(uint8_t bool);
void motor_set_speed(uint32_t speed);
void motor_set_direction(uint8_t dir);
void DAC_init(void);
void joystick_horizontal_to_speed(uint32_t joystick_output);
#endif /* MOTOR_CONTROLLER_H_ */