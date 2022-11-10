/*
 * node.h
 *
 * Created: 22.09.2022 15:27:57
 *  Author: akilanj
 */ 


#ifndef NODE_H_
#define NODE_H_

#include <stdio.h>

typedef void (*functionPtr)(void);

typedef struct Node {
	struct Node* parent;
	//struct Node* children[2] ;
	struct Node* next;
	struct Node* prev;
	char* name;
	uint8_t index;
	functionPtr nodeFunction;
} Node;



#endif /* NODE_H_ */