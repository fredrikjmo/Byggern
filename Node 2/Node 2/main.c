/*
 * Node 2.c
 *
 * Created: 12.10.2022 09:41:44
 * Author : fjmo
 */ 


#include "sam.h"
#include "uart_and_printf/printf-stdarg.h"
#include "can_node_2/can_controller.h"
#include "can_node_2/can_interrupt.h"
#include "Servo_and _IR/PWM.h"
#include "Servo_and _IR/ADC.h"
#include <inttypes.h>
#include "Servo_and _IR/goal.h"
#include "timer/timer.h"


#define can_br 0x01141255 
int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	configure_uart();
	can_init_def_tx_rx_mb(can_br);
	PWM_init();
	ADC_init();
	timer_init();
	
	
	WDT->WDT_MR = WDT_MR_WDDIS; // Disable WDT
	
	PIOA->PIO_OER = PIO_OER_P19 | PIO_OER_P20; // Output enable on PA19 and PA20
	
	PIOA->PIO_SODR = PIO_SODR_P19; // | PIO_SODR_P20; // Set PA19 and PA20 high ( Turn on both leds ) 
	
    /* Replace with your application code */
    while (1) 
    {	
		//PWM_update_dutycycle(7);
		
		//uint32_t goal_val = goal();
		
		
		printf("Hello \n\r");
		delay_ms(2000);
		printf("Heya!!!! \n\r");
		delay_ms(2000);
				
		
	    
		//printf("HELLOYYYYY\n\r");
    }
}
