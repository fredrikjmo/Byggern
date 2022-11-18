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
#include "motor/motor_controller.h"
#include "timer/timer.h"
#include "pid/pid.h"
#include "button/button.h"
#include <stdio.h>



#define can_br 0x01141255 
int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	configure_uart();
	can_init_def_tx_rx_mb(can_br);
	timer_init();
	PWM_init();
	ADC_init();
	motor_init();
	DAC_init();
	button_init();
	
	
	WDT->WDT_MR = WDT_MR_WDDIS; // Disable WDT
	
	//Turn on LEDs to indicate succesfull flash 
	PIOA->PIO_OER = PIO_OER_P19 | PIO_OER_P20; // Output enable on PA19 and PA20
	PIOA->PIO_SODR = PIO_SODR_P19; // | PIO_SODR_P20; // Set PA19 and PA20 high ( Turn on both leds ) 

	motor_disable_break(1);
    while (1) 
    {	
		motor_pid_controlled();
		if(goal()){
			CAN_MESSAGE* message;
			message->data[0] = 1;
			message->data_length = 1;
			message->id = 1;
			//can_send(message,0);}
	}
			//printf("Hey, you lost!\n\r");
		//}else {printf("Still playing\n\r");}
    }
}
