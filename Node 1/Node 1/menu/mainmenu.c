/*
 * mainmenu.h
 *
 * Created: 22.09.2022 15:40:12
 *  Author: akilanj
 */ 

#include "../menu/mainmenu.h"
#include "../OLED/OLEDdriver.h"
#include "../ADC/ADCdriver.h"
#include "../button/button.h"
#include <stdio.h>

void mainmenu_back (Node* currentNode){
	if (currentNode->parent != NULL)
		currentNode = currentNode->parent;
}
void mainmenu_print_current_menu ( Node* currentNode){
	uint8_t index = currentNode->index;
	OLED_clear_screen();
	
	while(1){
		currentNode = currentNode->next;
		OLED_goto_pos(currentNode->index, 20);
		printf(currentNode->name);

		if(index == currentNode->index)
			break;
	}
}

void mainmenu( void ){
	
	Node MainNode;

	// Initialize child-nodes

	Node FirstChild;
	Node SecondChild;
	Node ThirdChild;

	FirstChild.name = "First";
	FirstChild.next = &SecondChild;
	FirstChild.prev = &ThirdChild;
	FirstChild.parent = &MainNode;
	FirstChild.index = 0;
	
	SecondChild.name = "Second";
	SecondChild.next = &ThirdChild;
	SecondChild.prev = &FirstChild;
	SecondChild.parent = &MainNode;
	SecondChild.index = 1;

	ThirdChild.name = "Third";
	ThirdChild.next = &FirstChild;
	ThirdChild.prev = &SecondChild;
	ThirdChild.parent = &MainNode;
	ThirdChild.index = 2;


	//Initialize MainMenu-node
	
	MainNode.name = "Main";
	MainNode.next = NULL;
	MainNode.prev = NULL;
	Node* currentNode = &FirstChild;

	mainmenu_print_current_menu(currentNode);
	
	while (1)
	{
		adc_calibrate();
		
		uint8_t btn_val = button_joystick_read();
		direction dir = direction_read();

		if(dir == down){
				OLED_clear_area(currentNode->index,4,17);
				currentNode = currentNode->next;
				OLED_print_penis(currentNode->index,4);
			}

		if ( dir == up ){
				OLED_clear_area(currentNode->index,4,17);
				currentNode = currentNode->prev;
				OLED_print_penis(currentNode->index,4);
			}
		
		OLED_clear_page(6);
		OLED_goto_pos(6,5);
		printf("Button Val: %u", btn_val);

		_delay_ms(200);
	}
}
