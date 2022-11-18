/*
 * ADCdriver.c
 *
 * Created: 21.09.2022 17:27:36
 *  Author: akilanj
 */ 

#include "ADCdriver.h"

uint8_t m_max_x_value = 0;
uint8_t m_min_x_value = 255;
uint8_t m_middle_x_value = 0;

uint8_t m_max_y_value = 0;
uint8_t m_min_y_value = 255;
uint8_t m_middle_y_value = 0;

void adc_sample( void ){
	
	volatile char * ext_mem = ( char *) 0x1400;
	ext_mem [ 0 ] = 0x01;
}

uint8_t adc_read ( uint8_t channel ){
	
	adc_sample();
	
	while((PIND & 1<<PIND4) == 0 ){}// While BUSY is low, spin here

	volatile char * ext_mem = ( char *) 0x1400 ;
	uint8_t ch_0 = ext_mem [ 0 ];
	uint8_t ch_1 = ext_mem [ 0 ];
	uint8_t ch_2 = ext_mem [ 0 ];
	uint8_t ch_3 = ext_mem [ 0 ];
	
	switch (channel)
	{
		case 0:
		return ch_0;
		
		case 1:
		return ch_1;

		case 2:
		return ch_2;

		case 3:
		return ch_3;

		default:
		return 0;
	}
}

void adc_calibrate( void ){
	uint8_t adc_x = adc_read(0);
	uint8_t adc_y = adc_read(1);
	
	if(m_middle_x_value == 0)
	m_middle_x_value = adc_x;
	
	if(m_middle_y_value == 0)
	m_middle_y_value = adc_y;
	
	//setting max and min values for x-values of joystick
	if (adc_x > m_max_x_value)
	m_max_x_value = adc_x;

	if (adc_x < m_min_x_value)
	m_min_x_value = adc_x;

	//setting max and min values for y-values of joystick
	if (adc_y > m_max_y_value)
	m_max_y_value = adc_y;
	
	if (adc_y < m_min_y_value)
	m_min_y_value = adc_y;
}

pos_p adc_pos_read(void){
	
	pos_p posistion_percentage;
	int16_t adc_x = adc_read(0);
	int16_t adc_y = adc_read(1);

	if(adc_x <= m_middle_x_value)
	posistion_percentage.x_axis	= 100*(adc_x - m_middle_x_value)/(m_middle_x_value-m_min_x_value);
	else
	posistion_percentage.x_axis	= 100*(adc_x - m_middle_x_value)/(m_max_x_value-m_middle_x_value);

	if(adc_y <= m_middle_y_value)
	posistion_percentage.y_axis	= 100*(adc_y - m_middle_y_value)/(m_middle_y_value-m_min_y_value);
	else
	posistion_percentage.y_axis	= 100*(adc_y - m_middle_y_value)/(m_max_y_value-m_middle_y_value);
	
	return posistion_percentage;
}

direction adc_direction_read (void){
	pos_p posistion_percentage = adc_pos_read();
	if(abs(posistion_percentage.x_axis) < 5 && abs(posistion_percentage.y_axis) < 5)
		return neutral;

	if(abs(posistion_percentage.x_axis) < abs(posistion_percentage.y_axis)){
		if(posistion_percentage.y_axis < 0)
			return down;
	return up;}
	
	else{
		if(posistion_percentage.x_axis < 0)
			return left;
	return right;}
}




uint8_t adc_pos_left_slider(void){

	uint8_t L_slider = adc_read(2);

	return 100*L_slider/255;
}

uint8_t adc_pos_right_slider(void){

	uint8_t R_slider = adc_read(3);

	return 100*R_slider/255;
}
