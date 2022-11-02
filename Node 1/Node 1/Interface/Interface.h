/*
 * Interface.h
 *
 * Created: 27.10.2022 09:39:08
 *  Author: fjmo
 */ 


#ifndef INTERFACE_H_
#define INTERFACE_H_

void interface_joystick_direction_to_CAN (void);

void interface_joystick_horizontal_percentage_to_CAN (void);

void interface_send_MFB_data_to_CAN (void);

#endif /* INTERFACE_H_ */