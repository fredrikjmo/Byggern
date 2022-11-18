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



void mainmenu_play_game(){
	OLED_clear_screen();
	OLED_goto_pos(6, 20);
	printf("playing");
	while(1){
		//uint8_t can_data = CAN_receive();
		//if(can_data == 1){break;}

		uint8_t joy = adc_direction_read();
		adc_calibrate();
		interface_send_MFB_data_to_CAN();
		_delay_ms(200);
	}

	OLED_clear_screen();
	return;
}

void mainmenu_enter_childNode(Node* currentNode){
	if(currentNode->nodeFunction!= NULL){
		currentNode->nodeFunction();}
}

void mainmenu( void ){
	
	Node MainNode;

	// Initialize child-nodes

	Node FirstChild;
	Node SecondChild;
	Node ThirdChild;

	FirstChild.name = "Play game";
	FirstChild.next = &SecondChild;
	FirstChild.prev = &ThirdChild;
	FirstChild.parent = &MainNode;
	FirstChild.index = 0;
	FirstChild.nodeFunction = mainmenu_play_game;
	
	SecondChild.name = "Settings";
	SecondChild.next = &ThirdChild;
	SecondChild.prev = &FirstChild;
	SecondChild.parent = &MainNode;
	SecondChild.index = 1;
	FirstChild.nodeFunction = NULL;

	ThirdChild.name = "Quit";
	ThirdChild.next = &FirstChild;
	ThirdChild.prev = &SecondChild;
	ThirdChild.parent = &MainNode;
	ThirdChild.index = 2;
	FirstChild.nodeFunction = NULL;


	//Initialize MainMenu-node
	
	MainNode.name = "Main";
	MainNode.next = NULL;
	MainNode.prev = NULL;
	Node* currentNode = &FirstChild;

	OLED_clear_screen();
	mainmenu_print_current_menu(currentNode);
	
	while (1)
	{
		adc_calibrate();
		uint8_t btn_val = button_right_read();
		direction dir = adc_direction_read();

		if(dir == down){
				OLED_clear_area(currentNode->index,4,17);
				currentNode = currentNode->next;
				OLED_print_rounded_arrow(currentNode->index,4);
			}

		if ( dir == up ){
				OLED_clear_area(currentNode->index,4,17);
				currentNode = currentNode->prev;
				OLED_print_rounded_arrow(currentNode->index,4);
			}

		if (btn_val == 1 && currentNode == &FirstChild)
		{
			mainmenu_play_game();
		}
		
		OLED_clear_page(6);
		OLED_goto_pos(6,5);
		printf("Button Val: %u", btn_val);

		_delay_ms(200);
	}
}
