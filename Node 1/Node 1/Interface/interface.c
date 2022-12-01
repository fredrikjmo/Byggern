/*
 * interface.c
 *
 * Created: 27.10.2022 09:39:18
 *  Author: fjmo
 */ 

#include "Interface.h"
#include "../ADC/ADCdriver.h"
#include "../button/button.h"

void interface_joystick_direction_to_CAN (void){
	
	direction joystick_dir = adc_direction_read();
	
	CAN_MESSAGE message;
	message.data[0] = joystick_dir;
	message.data_length = 1;
	message.id = 0xFF0F;
	
	CAN_transmit(message);
	
}

void interface_joystick_horizontal_percentage_to_CAN (void){
	//Sends offsetted value between 0 and 100
	
	pos_p posistion_percentage = adc_pos_read();
	
	uint8_t PWM_percentage = (posistion_percentage.x_axis + 100)/2;

	CAN_MESSAGE message;
	message.data[0] = PWM_percentage;
	message.data_length = 1;
	message.id = 0xFF0F;
		

	CAN_transmit(message);
	
}
void interface_send_MFB_data_to_CAN (void){
	
	pos_p joystick_posistion_percentage = adc_pos_read();
	uint8_t joystick_PWM_percentage = (joystick_posistion_percentage.x_axis + 100)/2;
	
	uint8_t right_slider_posistion_percentage = adc_pos_right_slider();
	
	uint8_t right_button_val = button_right_read();
	
	CAN_MESSAGE message;
	message.data[0] = joystick_PWM_percentage;
	message.data[1] = right_slider_posistion_percentage;
	message.data[2] = right_button_val;
	message.data_length = 3;
	message.id = 0xFF0F;
	
	CAN_transmit(message);
}
