/*
 * mainmenu.h
 *
 * Created: 22.09.2022 15:39:31
 *  Author: akilanj
 */ 


#ifndef MAINMENU_H_
#define MAINMENU_H_

#include "node.h"

void mainmenu_back (Node* currentNode);

void mainmenu( void );

void mainmenu_print_current_menu ( Node* currentNode);

void mainmenu_play_game();

#endif /* MAINMENU_H_ */