//***************************************************************************\\
\\																															  				  //
//          This .cpp file contains the function definitions of the functions in the queue class.           \\
\\																																		      //
//***************************************************************************\\

// including user defined nide header
#include "node.h"

// constructor for the node class
node::node()
{
	// initializing data to default values.
	data.setAttackPoints(0);
	data.setDefensePoints(0);
	data.setCardNumber(0);
	data.setName("NOT SET");
	data.setCardType("NO TYPE");
	pNext = nullptr;
}

// destructor for the node class
node::~node()
{
}

// copy constructor for the node class. Takes card and stores it into a node
node::node(Card data)
{
	this->data = data;
	pNext = nullptr;
}

// Getter function for getting the card data
Card node::getData() const
{
	// returns private member data
	return data;
}

// getter function for getting the pNext private member
node* node::getNext()
{
	// returns private member pNext
	return pNext;
}

// setter function for setting the pNext private member
void node::setNext(node* pNext)
{
	this->pNext = pNext;
}

// setter function for setting the Card private member
void node::setCard(Card Cdata)
{
	data = Cdata;
}