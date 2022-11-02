/*
 * pid.h
 *
 * Created: 02.11.2022 09:09:22
 *  Author: akilanj
 */ 


#ifndef PID_H_
#define PID_H_


#define T_ms	100

#define K_p		2.8
#define K_i		0.7

void pid_update_e (void);
void pid_update_u (void);

int pid_get_u (void);

#endif /* PID_H_ */