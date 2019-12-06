//*****************************************************\\
\\																			             			 //
//    This header file contains the definition of the queue class          \\
\\																									 //
//*****************************************************\\

//Starting the safety code for our header
#ifndef DYNINTQUEUE_H
#define DYNINTQUEUE_H

// including the headers for this file
#include "mainHeader.h"
#include "Card.h"

// defining our queue class
class queue
{
	//private members of the queue class
private:
	// Structure for the queue nodes
	struct node
	{
		Card value;       // Card in the node
		node* next;		// Pointer to the next node
	};

	node* front;  // The front of the queue
	node* rear;   // The rear of the queue
	int numItems;      // Number of items in the queue

	// public members for our queue class
public:
	// Constructor for the queue class
	queue();

	// Destructor for the queue class
	~queue();

	// Queue operations
	void enqueue(Card);
	void dequeue(Card&);
	bool isEmpty() const;
	void clear();
};

// ending safety code for this header
#endif