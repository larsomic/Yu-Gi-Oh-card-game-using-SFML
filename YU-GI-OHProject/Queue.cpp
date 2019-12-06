//***************************************************************************\\
\\																															  				  //
//          This .cpp file contains the function definitions of the functions in the queue class.           \\
\\																																		      //
//***************************************************************************\\

// including user defined headers
#include "mainHeader.h"
#include "queue.h"

// Constructor for the queue class that initializes data.
queue::queue()
{
	front = nullptr;
	rear = nullptr;
	numItems = 0;
}

// Destructor for the queue class
queue::~queue()
{
	clear();
}

// Function enqueue inserts the value passed into it at the rear of the queue.
void queue::enqueue(Card num)
{
	// making a newNode and initializing it to null.
	node* newNode = nullptr;

	// Create a new node and store num there.
	newNode = new node;
	newNode->value = num;
	newNode->next = nullptr;

	// If the queue is empty then it makes front and rear new Node.
	if (isEmpty())
	{
		front = newNode;
		rear = newNode;
	}
	// If there is something in the queue then it stores new node into the rear
	else
	{
		rear->next = newNode;
		rear = newNode;
	}

	// Update numItems.
	numItems++;
}

// Function dequeue removes the value at the front of the queue, and copies it into num.
void queue::dequeue(Card& num)
{
	// makes a new node
	node* temp = nullptr;

	// if the queue is empty it prints a new line and flushes the stream.
	if (isEmpty())
	{
		cout << endl;
	}
	// if the queue contains data it changes the value of num and decreases the num items
	else
	{
		// Save the front node value in num.
		num = front->value;

		// Remove the front node and delete it.
		temp = front;
		front = front->next;
		delete temp;

		// Update numItems.
		numItems--;
	}
}

// Function definition for isEmpty returns true if the queue is empty, and false otherwise.
bool queue::isEmpty() const
{
	bool status;

	// if the private member num items is greater than one it returns false otherwise it returns true
	if (numItems > 0)
		status = false;
	else
		status = true;
	return status;
}

// Function clear dequeues all the elements in the queue.
void queue::clear()
{
	Card value;   // Dummy variable for dequeue

	// while the queue is not empty it keeps dequeueing
	while (!isEmpty())
	{
		dequeue(value);
	}
}