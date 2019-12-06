//************************************************************\\
\\			       																             			         //
//         This .cpp file contains the function definitions of the card class          \\
\\																									             //
//************************************************************\\

// including the card class we defined before
#include"Card.h"

// definition of the constructor for card class
Card::Card()
{
	// stores default values into all of the private members of Card
	name = "No Name";
	attackPoints = 0;
	defensePoints = 0;
	cardType = "Normal";
	cardNumber = 0;
}

// deconstructor for Card class
Card::~Card()
{
}

// setter for setting the name of the card
void Card::setName(string inputName)
{
	// storing whats passed into the function into the private member called name
	name = inputName;
}

// setter for setting the attack points of the card
void Card::setAttackPoints(int inputAttack)
{
	// storing whats passed into the function into the private member called attackPoints
	attackPoints = inputAttack;
}

// setter for setting the defense points of the card
void Card::setDefensePoints(int inputDefense)
{
	// storing whats passed into the function into the private member called defensePoints
	defensePoints = inputDefense;
}

// setter for setting the card type of the card
void Card::setCardType(string inputType)
{
	// storing whats passed into the function into the private member called cardType
	cardType = inputType;
}

// setter for setting the card number of the card
void Card::setCardNumber(int cardNum)
{
	// storing whats passed into the function into the private member called cardNumber
	cardNumber = cardNum;
}

// getter function for getting the contents of the private member name
string Card::getName()
{
	// returns the value of the private member name
	return name;
}

// getter function for getting the contents of the private member attackPoints
int Card::getAttackPoints()
{
	// returns the value of the private member attackPoints
	return attackPoints;
}

// getter function for getting the contents of the private member defensePoints
int Card::getDefensePoints()
{
	// returns the value of the private member defensePoints
	return defensePoints;
}

// getter function for getting the contents of the private member cardType
string Card::getCardType()
{
	// returns the value of the private member cardType
	return cardType;
}

// getter function for getting the contents of the private member cardNumber
int Card::getCardNum()
{
	// returns the value of the private member cardNumber
	return cardNumber;
}
