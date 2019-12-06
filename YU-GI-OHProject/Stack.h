//*****************************************************\\
\\																			             			 //
//     This header file contains the definition of the Stack class          \\
\\																									 //
//*****************************************************\\

// Beginning safety code for stack header
#ifndef STACK_H
#define STACK_H

// including headers we will use in this header
#include "node.h"

// definition of the stack class
class stack
{
	// public members of the stack class
public:
	//constructor for the stack
	stack();

	//copy constructor for the stack
	stack(const stack& copy);

	//stack deconstructor
	~stack();

	// stack functions
	void push(Card data);
	Card pop();
	Card peek();

	// private members of the stack class
private:
	// pointer to the top of the stack
	node* top;

	// creates a new node
	node* makeNode(Card data);

	// destroys the whole stack
	void destroyStack();
};

// ending safety code for our header
#endif // !STACK_H