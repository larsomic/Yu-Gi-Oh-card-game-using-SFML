//*****************************************************************************************************\\
\\																																															 //
//    This header file contains the definition of node class and it also contains the definition of all of the functions for this class.    \\
\\																																															 //
//*****************************************************************************************************\\

// Start of the safety code for this header
#ifndef NODE_H
#define NODE_H

//including two classes we previously defined to implement the card class and all of the other libraries 
#include "mainHeader.h"
#include "Card.h"

// definition of class node. Node contains a card and a pointer to the next node. This is used in our stack functionality
class node
{
	//public members for the node class
public:
	//constructor for node
	node();

	//destructor of node
	~node();

	//copy constructor
	node(Card data);

	// getters  for getting the address of the next node and for getting the current card
	Card getData() const;
	node* getNext();

	//settind the next pointer and the current card
	void setNext(node* pNext);
	void setCard(Card Cdata);

	// The private data members for Node class
private:
	// This is an instance of the card class from Card.h
	Card data;
	//pointer to the next node.
	node* pNext;
};

// ending safety code for this PA
#endif // !NODE_H