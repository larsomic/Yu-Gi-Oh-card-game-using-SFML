//****************************************************************************************\\
\\																																									 //
//    This header file contains the definitions of all functions used in this program that are not part of a class.      \\
\\																																									 //
//****************************************************************************************\\

// Beginning of safety code for this header
#ifndef PA6_HEADER_H
#define PA6_HEADER_H

// including user defined headers to make sure this header can "see" everything.
#include "mainHeader.h"
#include "Card.h"
#include "queue.h"
#include "stack.h"

// definition of all of our functions.

// This function controls the main menu. It displays images and text to the screen. It gets user input in the form of a mouse click, and calls
// different functions based off where they click
void display_menu_to_screen(sf::RenderWindow& window);

// This function does all the logic of playing the game it calls other functions too control the cards and it also keeps track of life points
void playGame(sf::RenderWindow& window, sf::Font font, sf::Event event1);

// This is where the trade implementation will go but it is not quite finished :)
int tradeScreen(sf::RenderWindow& window, sf::Font font, sf::Event& event1);

// This function returns 1 if a player exists and a 0 if the player has not been entered before
int checkPlayerExists(string arrayNames[], string inputName, int sizeArray);

// This functions gets the number of players from the file and returns the value
int getNumPlayers(ifstream& infile);

// This function fills an array with the names of players on file.
void fillPlayerArray(ifstream& inputStream, string playerNameArray[], int sizeArray);

// This function displays to the screen what someone types as a  P1 username and returns their name as a string.
string getP1Name(sf::RenderWindow& window, sf::Event event1, sf::Font font);

// This function displays p1's selection and gets player 2's selection as well. It returns what player2 enters as a string.
string getP2Name(sf::RenderWindow& window, sf::Event event1, sf::Font font, string P1Name);

//This function loads all fifty cards of the players into an array that is passed into it
void loadPlayerCards(Card playerCardArray[], string username);

// This function is called if a player does not exist yet. This function generates fifty random cards from all of the cards I have and saves them into an array
void generatePlayerCards(Card PlayerCards[], string PlayerName, Card allCards[]);

// This function opens the cards.csv file and stores its contents into an array
void loadAllCards(Card allCardArray[]);

// This function accepts the players array and shuffles it so you dont start with the same cards every single time that you play my game.
void shuffleCards(Card PlayerCards[]);

//  This function pops off the first five elements of the stack and puts them into an array for the players hand
void fillHand(stack* playerStack, Card PlayerHand[]);

// This function displays the players attack queue and defense queue as well as the players hand onto the window
int displayCards(sf::RenderWindow& window, Card playerCard[], sf::Font font, sf::Event event1, int attackOrDefense, queue* attackQueue, queue* defenseQueue);

// This function displays whos turn it is and how many life points they have left.
void startingGameScreen(sf::RenderWindow& window, sf::Event event1, string playerName, sf::Font font, int lifePoints);

// This function takes out whatever card they chose and then pops off the next card from the stack to replace the old card.
void updateCard(int cardChoice, Card playerHand[], stack* playersStack);

// This function fills the players stack with the elements of their shuffled array
void fillPlayerStack(stack* playerStack, Card playerCards[]);

// This function enqueues whatever card they choose into whatever queue is passed in
void addToQueue(queue* inQueue, int cardChoice, Card playersHand[]);

// This function displays the queues to the screen without disrupting the contents of them
void displayQueues(sf::RenderWindow& window, queue* attackQueue, queue* defenseQueue);

// this function accepts the four queues and dequeues their contents. It then sees who won and takes away the appropiate life points.
void gameLogic(queue* p1AttackQueue, queue* p1DefenseQueue, queue* p2AttackQueue, queue* p2DefenseQueue, int* p1Health, int* p2Health);

// This function prints out the winner by determing who's lifepoints are above 0
void winnerScreen(sf::RenderWindow& window, sf::Font font, string P1Name, string P2Name, int p1LifePoints, int p2LifePoints);

//ending safety code for this header
#endif 