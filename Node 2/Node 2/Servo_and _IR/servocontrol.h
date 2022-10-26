/*
 * servocontrol.h
 *
 * Created: 26.10.2022 10:48:04
 *  Author: akilanj
 */ 

#include <stdint.h>
#include "sam.h"

#ifndef SERVOCONTROL_H_
#define SERVOCONTROL_H_

#include "PWM.h"

void set_servo_posistion(uint32_t joystick_percentage);



#endif /* SERVOCONTROL_H_ */