//*****************************************************************************************************\\
\\																																															 //
//    This header file contains the definition of Card class and it also contains the definition of all of the functions for this class.    \\
\\																																															 //
//*****************************************************************************************************\\

//start of safety code for this header file
#ifndef CARDCLASS_H
#define CARDCLASS_H

// this is a user defined header that contains all of the general headers for this program
#include "mainHeader.h"

//definition of the Card class this class contains private members for all data that each individual card holds
// the public functions contain setters, getters, constructor, and deconstructor
class Card
{
	//private data members for card data
private:
	string name;
	int attackPoints;
	int defensePoints;
	string cardType;
	int cardNumber;
	// public functions for setters, getters, constructors, and deconstructors
public:
	// constrructor for the Card class
	Card();

	// deconstructor for Card class
	~Card();

	// setters for changing private data members of the class
	void setName(string inputName);
	void setAttackPoints(int inputAttack);
	void setDefensePoints(int inputDefense);
	void setCardType(string inputType);
	void setCardNumber(int cardNum);

	// getters for accessing the private data members of the class
	string getName();
	int getAttackPoints();
	int getDefensePoints();
	string getCardType();
	int getCardNum();
};

//ending safety code we "started before"
#endif