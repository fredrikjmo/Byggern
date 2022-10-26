/*
 * PWM.h
 *
 * Created: 19.10.2022 09:03:10
 *  Author: akilanj
 */ 

#include <stdint.h>
#include "sam.h"

#ifndef PWM_H_
#define PWM_H_

void PWM_init(void);

void PWM_update_dutycycle(uint32_t percentage);





#endif /* PWM_H_ */