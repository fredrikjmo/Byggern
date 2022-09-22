/*
 * node.h
 *
 * Created: 22.09.2022 15:27:57
 *  Author: akilanj
 */ 


#ifndef NODE_H_
#define NODE_H_

typedef struct Node {
	struct Node* parent;
	//struct Node* children[2] ;
	struct Node* currentChild;
	struct Node* next;
	struct Node* prev;
	char* name;
} Node;

#endif /* NODE_H_ */