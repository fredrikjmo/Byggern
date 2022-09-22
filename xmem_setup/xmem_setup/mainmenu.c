/*
 * mainmenu.h
 *
 * Created: 22.09.2022 15:40:12
 *  Author: akilanj
 */ 

#include "mainmenu.h"
#include "OLEDdriver.h"
#include "ADCdriver.h"
#include <stdio.h>

void mainmenu( void ){
	
	//Node mainNode;
		//
	//mainNode.name = "Main Menu";
	//mainNode.next = NULL;
	//mainNode.prev = NULL;
	//mainNode.parent = NULL;
	//
//
	////Initialize first child
	//mainNode.children[0]->name = "First";
	//mainNode.children[0]->next = mainNode.children[1];
	//mainNode.children[0]->prev = mainNode.children[1];
	//mainNode.children[0]->parent = &mainNode; 
	//mainNode.children[0]->currentChild = NULL;
	//mainNode.children[0]->children = { NULL };
	//
	////Initialize second child
	//mainNode.children[1]->name = "Second";
	//mainNode.children[1]->next = mainNode.children[0];
	//mainNode.children[1]->prev = mainNode.children[0];
	//mainNode.children[1]->parent = &mainNode;
	//mainNode.children[1]->currentChild = NULL; 
	//
	//mainNode.currentChild = mainNode.children[0];
	//
//


	Node MainNode;

	//Initialize child-nodes

	Node FirstChild;
	Node SecondChild;
	Node ThirdChild;

	FirstChild.name = "First";
	FirstChild.next = &SecondChild;
	FirstChild.prev = &ThirdChild;
	FirstChild.currentChild = NULL;
	FirstChild.parent = &MainNode;

	SecondChild.name = "Second";
	SecondChild.next = &ThirdChild;
	SecondChild.prev = &FirstChild;
	SecondChild.currentChild = NULL;
	SecondChild.parent = &MainNode;

	ThirdChild.name = "Third";
	ThirdChild.next = &FirstChild;
	ThirdChild.prev = &SecondChild;
	ThirdChild.currentChild = NULL;
	ThirdChild.parent = &MainNode;


	//Initialize MainMenu-node
	
	MainNode.name = "Main";
	MainNode.next = NULL;
	MainNode.prev = NULL;
	MainNode.currentChild = &FirstChild;






	//char * name = "Hadeland";
	while (1)
	{	
		pos_p p = pos_read();
		adc_calibrate();
		direction dir = direction_read();
		OLED_clear_screen();
		OLED_goto_pos(4, 20);
		
		if(dir == up){
			
			MainNode.currentChild = MainNode.currentChild->next;


			//Node* buffernode =  mainNode.currentChild->next;
			//mainNode.currentChild = buffernode;
			//printf("up");
			
		}

		if ( dir == down ){

			MainNode.currentChild = MainNode.currentChild->prev;


			//Node* buffernode =  mainNode.currentChild->prev;
			//mainNode.currentChild = buffernode;
			//printf("down");
		}
		
		
		printf(MainNode.currentChild->name);
		//printf("   %d \n\r", dir);
		
		_delay_ms(200);
	}
}
