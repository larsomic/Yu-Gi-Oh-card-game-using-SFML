//***************************************************************************\\
\\																																			  //
//          This .cpp file contains the function definitions of the functions in the stack class.            \\
\\																																		      //
//***************************************************************************\\

// including the user defined stack class
#include "stack.h"

// constructor for the stack class
stack::stack()
{
	// sets the private member top to be a null pointer
	top = nullptr;
}

// copy constructor for the stack class. Stores what is being passed into it into the private member top.
stack::stack(const stack& copy)
{
	// copies the pointer passed into it into the top private member.
	top = copy.top;
}

// destructor for the stack class.
stack::~stack()
{
	// calls destroy stack to delete the stack 
	destroyStack();
}

// decleration of the push function for putting data onto the stack.
void stack::push(Card data)
{
	// stores data into pmem
	node* pmem = makeNode(data);

	// makes sure that pmem is not null
	if (pmem != nullptr)
	{
		// if there is no top it stores pmem into the top of the stack.
		if (top == nullptr)
		{
			top = pmem;
		}
		// if there is data in the stack then it stores it to the top of the stack 
		else
		{
			pmem->setNext(top);
			top = pmem;
		}
	}
}

// decleration of the pop function for taking data off of the stack.
Card stack::pop()
{
	// makes sure the stack is not empty
	if (top != nullptr)
	{
		// gets the data from top and stores it into a temporary card
		Card data = top->getData();

		// moves top to the next position.
		node* temp = top;
		top = top->getNext();

		// frees the temp node
		delete temp;

		// returns the card that has the top of the stack stored into it.
		return data;
	}

	// if the stack is empty then we make a new card and set its card number to 1000 this is to check for failure 
	Card failure;
	failure.setCardNumber(1000);

	// returns the failure card
	return failure;
}

// decleration of the peek function for looking at the top of the data without removing any data.
Card stack::peek()
{
	// checks to see if the stack is empty
	if (top != nullptr)
	{
		// returns the data thats at the top of the stack
		return top->getData();
	}

	// If the stack is empty it makes a card.
	Card failure;

	//Setting card number to 1000 will indicate that we got to failure
	failure.setCardNumber(1000);

	// returns the failure card
	return failure;
}
 
// The definition for a function that will make a new node.
node* stack::makeNode(Card data)
{
	// allocates memory for a new node and returns the pointer to it.
	return new node(data);
}

// The definition for a function that destroys the entire stack.
void stack::destroyStack()
{
	// While the top is not empty it will pop cards off of the stack.
	while (top != nullptr)
	{
		pop();
	}
}