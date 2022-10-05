/*
 * xmem_setup.c
 *
 * Created: 07.09.2022 09:02:38
 * Author : akilanj
 */ 
#include <avr/io.h>
#define F_CPU 4.9152E6

#include <util/delay.h>
#include "XMEMdriver.h"
#include "ADCdriver.h"
#include "USARTdriver.h"
#include "OLEDdriver.h"
#include "mainmenu.h"

// USART_Init( MYUBRR );

int main(void)
{
	xmem_init();
	adc_init();
	//USART_Init(MYUBRR);
	
	OLED_init();
	OLED_clear_screen();
	mainmenu();
	
	//while(1){
		//OLED_clear_screen();
		//OLED_goto_pos(4, 20);
		//
		//pos_p p = pos_read();
		//adc_calibrate();
		//direction dir = direction_read();
		//
		////printf("Dir: %d ", dir);
	//
//
		//
		//
		//_delay_ms(40);
	//
	//}
	//
	
	
	
	//while(1){
		//OLED_clear_screen();
		//adc_calibrate();
		//pos_p p = pos_read();
		//uint8_t l = pos_left_slider();		//uint8_t r = pos_right_slider();//
		//OLED_goto_pos(0,0);
		//printf("X: %d", p.x_axis);
		//OLED_goto_pos(2,0);
		//printf("Y: %d", p.y_axis);
		//OLED_goto_pos(4,0);
		//printf("Left: %d", l);
		//OLED_goto_pos(5,0);
		//printf("Right: %d", r);
		//
		//_delay_ms(40);
	//}
	
			
	

	
		
	

}
 