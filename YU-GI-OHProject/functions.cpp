//******************************************************************************************************\\
\\			       																             			                                                                                       //
//         This .cpp file contains all of the function definitions for functions not in a class. This all of the brains of the function.          \\
\\																						                                                                                			            //
//******************************************************************************************************\\

// includes the main header file for our program
#include "Card.h"
#include "functionHeader.h"
#include "stack.h"
#include "queue.h"

// This function is all of the code for the main menu portion of game
void display_menu_to_screen(sf::RenderWindow& window)
{
	// Creating a rectangle the size of the users screen. THis rectangle is for the yu-gi-oh image.
	sf::RectangleShape player(sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height - 156));

	// Creating a texture
	sf::Texture playerTexture;

	// Loading an image from the file
	playerTexture.loadFromFile("main_menu_image.png");

	// Placing the texture onto the rectangle
	player.setTexture(&playerTexture);

	// Creating rectangles for each of the boxes
	sf::RectangleShape boxPlay(sf::Vector2f(530, 200)), boxExit(sf::Vector2f(410, 200)), boxRules(sf::Vector2f(530, 200));

	// Setting the attributes of the rectangles we just defined.
	boxPlay.setFillColor(sf::Color::Black);
	boxPlay.setPosition(1730, 1760);
	boxExit.setFillColor(sf::Color::Black);
	boxExit.setPosition(250, 1760);
	boxRules.setFillColor(sf::Color::Black);
	boxRules.setPosition(3170, 1760);

	// Creating a new event
	sf::Event event1;

	// Creating and loading fonts for this file
	sf::Font font;
	font.loadFromFile("LucidaBrightRegular.ttf");

	// Creating text variables for displaying words to the screen.
	sf::Text playText, exitText, rulesText;

	// Setting strings for the text variables.
	playText.setString("Play!");
	exitText.setString("Exit");
	rulesText.setString("Trade");

	// Setting fonts for the text variables.
	playText.setFont(font);
	exitText.setFont(font);
	rulesText.setFont(font);

	//Setting char size for the text variables.
	playText.setCharacterSize(200);
	exitText.setCharacterSize(200);
	rulesText.setCharacterSize(200);

	// Setting the position of the font for the text variables.
	playText.setPosition(1770, 1720);
	exitText.setPosition(270, 1720);
	rulesText.setPosition(3170, 1720);

	// Setting fill color for the text variables.
	playText.setFillColor(sf::Color::Color(100, 100, 100));
	exitText.setFillColor(sf::Color::Color(100, 100, 100));
	rulesText.setFillColor(sf::Color::Color(100, 100, 100));

	// While the window is still open it keeps running
	while (window.isOpen())
	{
		// Gets the event that happened in the window
		while (window.pollEvent(event1))
		{
			switch (event1.type)
			{
				// If the user closes the window
			case sf::Event::Closed:
				window.close(); // Closes the window
				break;
			}
		}

		// Vector of the mouse position on screen
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);

		// Gets vectors for the size and position of each box
		sf::Vector2f boxPlayVectorLocation = boxPlay.getPosition();
		sf::Vector2f boxPlayVectorSize = boxPlay.getSize();

		sf::Vector2f boxExitVectorLocation = boxExit.getPosition();
		sf::Vector2f boxExitVectorSize = boxExit.getSize();

		sf::Vector2f boxRulesVectorLocation = boxRules.getPosition();
		sf::Vector2f boxRulesVectorSize = boxRules.getSize();

		// This is for seeing which box they click. If the mouse is in the box change the fill color.
		if (mousePos.x >= boxPlayVectorLocation.x && mousePos.x <= (boxPlayVectorLocation.x + boxPlayVectorSize.x) && mousePos.y >= boxPlayVectorLocation.y && mousePos.y <= (boxPlayVectorLocation.y + boxPlayVectorSize.y))
		{
			playText.setFillColor(sf::Color::Color(244, 41, 65));
			// If the user clicks the screen play the game.
			if (event1.type == sf::Event::MouseButtonPressed)
			{
				playGame(window, font, event1);
			}
		}
		// If the mouse isn't in the box reset the fill color
		else
		{
			playText.setFillColor(sf::Color::Color(100, 100, 100));
		}

		// This is for seeing which box they click. If the mouse is in the box change the fill color.
		if (mousePos.x >= boxExitVectorLocation.x && mousePos.x <= (boxExitVectorLocation.x + boxExitVectorSize.x) && mousePos.y >= boxExitVectorLocation.y && mousePos.y <= (boxExitVectorLocation.y + boxExitVectorSize.y))
		{
			exitText.setFillColor(sf::Color::Color(244, 41, 65));
			// If the user clicks the screen play the game.
			if (event1.type == sf::Event::MouseButtonPressed)
			{
				window.close();
			}
		}
		// If the mouse isn't in the box reset the fill color
		else
		{
			exitText.setFillColor(sf::Color::Color(100, 100, 100));
		}

		// Used to see if they wanted to leave the trade function
		int truth = 0;

		// This is for seeing which box they click. If the mouse is in the box change the fill color.
		if (mousePos.x >= boxRulesVectorLocation.x && mousePos.x <= (boxRulesVectorLocation.x + boxRulesVectorSize.x) && mousePos.y >= boxRulesVectorLocation.y && mousePos.y <= (boxRulesVectorLocation.y + boxRulesVectorSize.y))
		{
			// Sets the color to red if the mouse is over the box
			rulesText.setFillColor(sf::Color::Color(244, 41, 65));

			// If mouse is pressed over the button it calls trade screen.
			if (event1.type == sf::Event::MouseButtonPressed)
			{
				// While they didn't click leave it keeps calling trade screen
				while (truth != 1)
				{
					truth = tradeScreen(window, font, event1);
				}
			}
		}
		// If the mouse is not within the rectangle then it changes the color to grey
		else
		{
			rulesText.setFillColor(sf::Color::Color(100, 100, 100));
		}

		// Draws evrything to the screen
		window.clear();
		window.draw(player);
		window.draw(boxPlay);
		window.draw(boxRules);
		window.draw(boxExit);
		window.draw(playText);
		window.draw(exitText);
		window.draw(rulesText);
		window.display();
	}
}

// This function plays the actual game
void playGame(sf::RenderWindow& window, sf::Font font, sf::Event event1)
{
	// Creating five arrays for each players cards, all the cards, and th eplayers hands
	Card P1Cards[50], P2Cards[50], allCards[133], P1Hand[5], P2Hand[5];

	// Setting the players life points to 8000
	int p1LifePoints = 8000, p2LifePoints = 8000;

	// Clears the screen so we arent looking at the main menu anymore
	window.clear();
	window.display();

	// Creating an input file variable
	ifstream playerFile;

	// Opening the file in append mode
	playerFile.open("players_file.txt", ios_base::app);

	// Creating two integer variables
	int numPlayers = 0, playerExists;

	// Calling get number of players
	numPlayers = getNumPlayers(playerFile);
	string* playerArray;

	playerArray = new string[numPlayers];

	// Closes the player file
	playerFile.close();

	// Creating a new event
	sf::Event event3;

	// Getting what happens on the screen
	while (window.pollEvent(event3))
	{

	}
	// If they clicked on the x in the op right close the window and return
	if (event3.type == sf::Event::Closed)
	{
		window.close();
		return;
	}

	//Loads all of the cards from a file
	loadAllCards(allCards);

	// declares variables for the players name
	string P1Name, P2Name, temp;

	// calls a function that gets player name. Returns string of player name for P1
	P1Name = getP1Name(window, event1, font);

	// reopens file so that we are at the start of the fule again
	playerFile.open("players_file.txt", ios_base::app);

	//fills player array with file contents
	fillPlayerArray(playerFile, playerArray, numPlayers);

	// Closes player file
	playerFile.close();

	// calls a function to check if the player exits. If it exists it returns 1 if it doesnt it returns 0;
	playerExists = checkPlayerExists(playerArray, P1Name, numPlayers);

	// If the player exists
	if (playerExists == 1)
	{
		//load cards in from file;
		loadPlayerCards(P1Cards, P1Name);
	}
	// If player doesn't exist
	else if (playerExists == 0)
	{
		// this function updates player log with the new player name and generates them fifty cards that then gets put into their notepad file
		generatePlayerCards(P1Cards, P1Name, allCards);

		// Creating an output stream
		ofstream outputName;

		// Opening the file in append mode
		outputName.open("players_file.txt", ios_base::app);

		// Puts the players name into the file
		outputName << P1Name << "\n";

		// CLoses file
		outputName.close();
	}
	// Gets players name
	P2Name = getP2Name(window, event1, font, P1Name);

	// Checks to see if the player exists
	playerExists = checkPlayerExists(playerArray, P2Name, numPlayers);

	// If they exist
	if (playerExists == 1)
	{
		//load cards in from file;
		loadPlayerCards(P2Cards, P2Name);
	}
	// If the player doesn't exist
	else if (playerExists == 0)
	{
		// Generates the player fifty cards
		generatePlayerCards(P2Cards, P2Name, allCards);

		// Creating an output stream
		ofstream outputName;

		// Opening the file for append
		outputName.open("players_file.txt", ios_base::app);

		// Prints the players  name into the file
		outputName << P2Name << "\n";

		// Closes file
		outputName.close();
	}

	// Shuffles the two decks
	shuffleCards(P1Cards);
	shuffleCards(P2Cards);

	// Making a card stack for each player
	stack p1CardStack, p2CardStack;

	// Takes the players array and puts it into the stack
	fillPlayerStack(&p1CardStack, P1Cards);
	fillPlayerStack(&p2CardStack, P2Cards);

	// Fills the players hand
	fillHand(&p1CardStack, P1Hand);
	fillHand(&p2CardStack, P2Hand);

	// Integer for holding which card they chose
	int cardChoice;

	// Making queues for the atack and defense queues of both players
	queue p1AttackQueue, p1DefenseQueue, p2AttackQueue, p2DefenseQueue;

	// Stays in the loop while both players have positive life points
	while (p1LifePoints > 0 && p2LifePoints > 0)
	{
		// Displays start screen for player one
		startingGameScreen(window, event1, P1Name, font, p1LifePoints);

		// Displays the players cards and returns which card they chose
		cardChoice = displayCards(window, P1Hand, font, event1, 1, &p1AttackQueue, &p1DefenseQueue);

		// Adds their choice to their queue
		addToQueue(&p1AttackQueue, cardChoice, P1Hand);

		// Replaces the card they used
		updateCard(cardChoice, P1Hand, &p1CardStack);

		// Displays the defense cards for them to chose
		cardChoice = displayCards(window, P1Hand, font, event1, 2, &p1AttackQueue, &p1DefenseQueue);

		// Adds their choice to their queue
		addToQueue(&p1DefenseQueue, cardChoice, P1Hand);

		// Replaces the card they used
		updateCard(cardChoice, P1Hand, &p1CardStack);
		
		// Displays start screen for player2
		startingGameScreen(window, event1, P2Name, font, p2LifePoints);

		// Displays the players cards and returns which card they chose
		cardChoice = displayCards(window, P2Hand, font, event1, 1, &p2AttackQueue, &p2DefenseQueue);

		// Adds their choice to their queue
		addToQueue(&p2AttackQueue, cardChoice, P2Hand);

		// Replaces the card they used
		updateCard(cardChoice, P2Hand, &p2CardStack);

		// Displays the defense cards for them to chose
		cardChoice = displayCards(window, P2Hand, font, event1, 2, &p2AttackQueue, &p2DefenseQueue);

		// Adds their choice to their queue
		addToQueue(&p2DefenseQueue, cardChoice, P2Hand);

		// Replaces the card they used
		updateCard(cardChoice, P2Hand, &p2CardStack);

		// Determining what happened in that turn.
		gameLogic(&p1AttackQueue, &p1DefenseQueue, &p2AttackQueue, &p2DefenseQueue, &p1LifePoints, &p2LifePoints);
	}
	// Displays the winner screen once one of the players life points is below.
	winnerScreen(window, font, P1Name, P2Name, p1LifePoints, p2LifePoints);
}

// This function is used for displaying the trade screen
int tradeScreen(sf::RenderWindow& window, sf::Font font, sf::Event& event1)
{
	// Creating two text variables for displaying stuff to the screen
	sf::Text trade, returnMenu;

	// Setting atributes of the text
	trade.setString("This isn't done sorry");
	trade.setPosition(sf::Vector2f(500, 500));
	trade.setFont(font);
	trade.setCharacterSize(150);

	returnMenu.setString("Return");
	returnMenu.setFont(font);
	returnMenu.setCharacterSize(100);
	returnMenu.setPosition(sf::Vector2f(90, -10));
	returnMenu.setFillColor(sf::Color::White);

	// Creating two rectangles each with size 100 100
	sf::RectangleShape whiteBackground(sf::Vector2f(100, 100)), backArrow(sf::Vector2f(100, 100));
	
	// Setting fill color for rectangle
	whiteBackground.setFillColor(sf::Color::White);

	// Creating a texture
	sf::Texture arrowImage;

	// Loading image into texture
	arrowImage.loadFromFile("backArrow.png");

	// Putting texture on the rectangle
	backArrow.setTexture(&arrowImage);

	// Making a new vector which has the mouse position
	sf::Vector2i mousePos = sf::Mouse::getPosition();

	// Getting what happens on the screen
	window.pollEvent(event1);

	// If the mouse is within the box it changes the color of the rectangles to red
	if ((mousePos.x >= 0 && mousePos.x <= 420) && (mousePos.y >= 60 && mousePos.y <= 180))
	{
		whiteBackground.setFillColor(sf::Color::Color(244, 41, 65));
		returnMenu.setFillColor(sf::Color::Color(244, 41, 65));

		// If they click return  it returns 1 to indicate they wanted to leave
		if (event1.type == sf::Event::MouseButtonPressed)
		{
			return 1;
		}
	}
	// If they are not within the box the colors are set to white
	else
	{
		whiteBackground.setFillColor(sf::Color::White);
		returnMenu.setFillColor(sf::Color::White);
	}

	// Displays all the text onto the screen
	window.clear();
	window.draw(trade);
	window.draw(whiteBackground);
	window.draw(backArrow);
	window.draw(returnMenu);
	window.display();
	window.clear();
	window.draw(trade);
	window.draw(whiteBackground);
	window.draw(backArrow);
	window.draw(returnMenu);
	window.display();
}

// This function checks to see if the player exists. If they do it returns 1 if they don't exist it returns 0.
int checkPlayerExists(string arrayNames[], string inputName, int sizeArray)
{
	// Creating a variable to tell if the user exists
	int playerExists = 0;

	// Runs while its less than the number of players in the array
	for (int count = 0; count < sizeArray; count++)
	{
		// If the input name is one of the names in the array it changes player exists to 1
		if (inputName == arrayNames[count])
		{
			playerExists = 1;
		}
	}

	// Returns if the player exists
	return playerExists;
}

// This player gets the num of players and returns it as an integer
int getNumPlayers(ifstream& playerFile)
{
	// Creating an integer for storing the number of players
	int  numPlayers = 0;

	// Creates a string for storing in the players name from the file
	string playerNames;

	// runs while the file isn't empty
	do
	{
		// Gets a line from the file
		getline(playerFile, playerNames);

		// Incraments the number of players
		numPlayers++;
	} while (!playerFile.eof());

	// Returns the number of players
	return numPlayers;
}

//This function fills the player name array with the players in file
void fillPlayerArray(ifstream& inputStream, string playerNameArray[], int sizeArray)
{ 
	// Runs howver many players are on file
	for (int count = 0; count < sizeArray; count++)
	{
		// stores their name into the player array
		getline(inputStream, playerNameArray[count]);
	}
}

// This function gets the player1 name and returns it as a string
string getP1Name(sf::RenderWindow& window, sf::Event event1, sf::Font font)
{
	// Clears the screen
	window.clear();

	// Makes two new text variables for displaying it on the screen.
	sf::Text loginText, enterNameTextP1, oneChar;

	// Setting the attributes of the text variables
	loginText.setFont(font);
	loginText.setCharacterSize(100);
	loginText.setString("Login");

	enterNameTextP1.setFont(font);
	enterNameTextP1.setCharacterSize(100);
	enterNameTextP1.setString("Player 1 Username:");
	enterNameTextP1.setPosition(0, 100);

	oneChar.setFont(font);
	oneChar.setPosition(300, 100);
	oneChar.setCharacterSize(100);

	// Draws the text and displays it
	window.clear();
	window.draw(loginText);
	window.draw(enterNameTextP1);
	window.display();

	// Creating a string variable for accepting the players name
	string inputString = "";
	
	// setting the initial x position of the name
	int movement_x = 1000;

	// Runs while the 
	while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		// Gets what happens on the screen
		while (window.pollEvent(event1))
		{
			switch (event1.type)
			{
				// If text is entered it enters here
			case sf::Event::TextEntered:
				// If the text is an enlgish character it goes here
				if (event1.text.unicode < 128)
				{
					// Adds the text to the string
					inputString += (char)event1.text.unicode;

					// Places the string onto the screen
					oneChar.setPosition(movement_x, 100);

					// Sets the value of string
					oneChar.setString(inputString);
				}
			}
		}

		// Draws and displays everything to the screen
		window.draw(loginText);
		window.draw(enterNameTextP1);
		window.draw(oneChar);
		window.display();
	}

	// Returning the players name
	return inputString;
}

// This function gets the player2 name and returns it as a string
string getP2Name(sf::RenderWindow& window, sf::Event event1, sf::Font font, string P1Name)
{
	// Pauses the application so that the events still work
	Sleep(300);

	// Creating a new event variable
	sf::Event event2;

	// Creating a new string variable
	string inputString = "";

	// Clears the screen
	window.clear();

	// Creating text variables so I can display stuff to the screen.
	sf::Text loginText, enterNameTextP1, p1Username, enterNameTextP2, oneChar;

	// Setting attributes of the text instances so I can display them to the string. It is only in braces so I can minimize it in visual studios
	{
		loginText.setFont(font);
		loginText.setCharacterSize(100);
		loginText.setString("Login");

		enterNameTextP1.setFont(font);
		enterNameTextP1.setCharacterSize(100);
		enterNameTextP1.setString("Player 1 Username:");
		enterNameTextP1.setPosition(0, 100);

		p1Username.setFont(font);
		p1Username.setCharacterSize(100);
		p1Username.setString(P1Name);
		p1Username.setPosition(1000, 100);

		enterNameTextP2.setFont(font);
		enterNameTextP2.setCharacterSize(100);
		enterNameTextP2.setString("Player 2 Username:");
		enterNameTextP2.setPosition(0, 200);

		oneChar.setFont(font);
		oneChar.setPosition(300, 200);
		oneChar.setCharacterSize(100);
	}

	// Displaying all of the text to both stringa
	window.clear();
	window.draw(loginText);
	window.draw(enterNameTextP1);
	window.draw(p1Username);
	window.draw(enterNameTextP2);
	window.display();

	window.draw(loginText);
	window.draw(enterNameTextP1);
	window.draw(p1Username);
	window.draw(enterNameTextP2);
	window.display();

	// Setting the initial x movement so things get placed in the correct spot
	int movement_x = 1000;

	// While loop that runs while the user has not clicked the enter key
	while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		// Gets an event from the screen and stores it into event2
		while (window.pollEvent(event2))
		{
			switch (event2.type)
			{
				// If the event is them entering text it goes here
			case sf::Event::TextEntered:
				// If they entered an english char
				if (event2.text.unicode < 128)
				{
					// Adds the char to the string
					inputString += (char)event2.text.unicode;

					// Moves the text to the correct position
					oneChar.setPosition(movement_x, 200);

					// Sets the value of the string
					oneChar.setString(inputString);
				}
			}
		}
		// Draws the string to the screen and displays it
		window.draw(oneChar);
		window.display();
	}

	// Erases the first part of the string
	inputString.erase(inputString.begin());

	// Returns the players name
	return inputString;
}

// This function loads the cards from a players file and stores it into their array.
void loadPlayerCards(Card playerCardArray[], string username)
{
	// Adding the .txt so the computer knows which file to open
	username = username + ".txt";

	// Creating an instream variable
	ifstream playerFile;

	// Opening the correct file.
	playerFile.open(username);

	// Creating string variables to store the data from the file
	string oneCard, delimiter = ",", tempString[5];

	// Creating integer variables to store the integer values
	int attackPoints, defensePoints, cardnum;

	// This loop runs fifty times for each of the cards the player has.
	for (int count = 0; count < 50; count++)
	{
		// Gets a line from the file
		getline(playerFile, oneCard);

		// Runs five times for each of the cards data values.
		for (int count2 = 0; count2 < 5; count2++)
		{
			// Splits the line on the first comma and stores it into the array of data
			tempString[count2] = oneCard.substr(0, oneCard.find(delimiter));

			// Changes the string so its only from the delimiter to the end of the string.
			oneCard = oneCard.substr(oneCard.find(delimiter) + 1, oneCard.length());
		}
		// Changes the strings to integers
		attackPoints = stoi(tempString[2]);
		defensePoints = stoi(tempString[3]);
		cardnum = stoi(tempString[4]);

		// Sets the data into the array of cards.
		playerCardArray[count].setName(tempString[0]);
		playerCardArray[count].setAttackPoints(attackPoints);
		playerCardArray[count].setDefensePoints(defensePoints);
		playerCardArray[count].setCardType(tempString[1]);
		playerCardArray[count].setCardNumber(cardnum);
	}
}

// This function loads in all of the cards from the file and stores them into an array.
void loadAllCards(Card allCardArray[])
{
	// Creating an instream variable
	ifstream cardFile;

	// Opening the card file
	cardFile.open("Cards.csv");

	// Creating string variables for storing data
	string oneCard, delimiter = ",", tempString[7];

	// Creating integer variables for storing card data
	int attackPoints, defensePoints, cardnumber;

	// This loop runs  133 times for each of the possible cards
	for (int count = 0; count < 133; count++)
	{
		// Getting a line from the file. Which contains one cards data.
		getline(cardFile, oneCard);

		// This loop runs 7 times for each of the card stats.
		for (int count2 = 0; count2 < 7; count2++)
		{
			// Splits the line on the first comma and stores it into the array of data
			tempString[count2] = oneCard.substr(0, oneCard.find(delimiter));

			// Changes the string so its only from the delimiter to the end of the string.
			oneCard = oneCard.substr(oneCard.find(delimiter) + 1, oneCard.length());
		}
		// Changes the strings to integers
		attackPoints = stoi(tempString[4]);
		defensePoints = stoi(tempString[5]);
		cardnumber = stoi(tempString[6]);

		// Sets the data into the array of cards.
		allCardArray[count].setName(tempString[0]);
		allCardArray[count].setAttackPoints(attackPoints);
		allCardArray[count].setDefensePoints(defensePoints);
		allCardArray[count].setCardType(tempString[2]);
		allCardArray[count].setCardNumber(cardnumber);
	}
}

// This function generates fifty cards for the player if they did not exist before.
void generatePlayerCards(Card PlayerCards[], string PlayerName, Card allCards[])
{
	// Adds .txt to the players name so that the computer can make a file for it
	PlayerName = PlayerName + ".txt";

	// Seeds the random number
	srand(time(NULL) * rand());

	// Creates an array of size 133 for each of the possible cards and other integer variables.
	int allNums[133] = { 0 }, randNums[50], num, count = 0;

	// This loop runs fifty times for each card in their file
	while (count < 50)
	{
		// Generates a random number from 0 and 132
		num = rand() % 133;

		// This runs if the randomly chosen card has already been chosen
		while (allNums[num] != 0)
		{
			// Generates a new card
			num = rand() % 133;
		}

		// Stores the random number into the array
		randNums[count] = num;

		// CHanges num to 1 so we know it has been used.
		allNums[num] = 1;

		// Incraments count
		count++;
	}

	// Creates a new output stream operator
	ofstream outputCards;

	// Creates a new file with the players name
	outputCards.open(PlayerName);

	// This loop runs fifty times for each card in their file
	for (int count = 0; count < 50; count++)
	{
		// Gets a card and stores it into the players array
		PlayerCards[count] = allCards[randNums[count]];

		// Prints out the cards information into the file.
		outputCards << PlayerCards[count].getName() << "," << PlayerCards[count].getCardType() << "," << PlayerCards[count].getAttackPoints() << "," << PlayerCards[count].getDefensePoints() << "," << PlayerCards[count].getCardNum() << endl;
	}

	// Closes output file
	outputCards.close();
}

// This function is used to take an array of cards and change the order of the cards in the array
void shuffleCards(Card PlayerCards[])
{
	// Seeds the random number so we don't get the same number everytime we run the program.
	srand(rand() * time(NULL));

	// Creating a temporary array of Cards.
	Card tempCards[50];

	// Creating arrays of integers and other integer variables
	int allNums[50] = { 0 }, randNums[50], num, count = 0;

	// This loop runs fifty times for each card in their file
	while (count < 50)
	{
		// Creates a copy of the input array
		tempCards[count] = PlayerCards[count];
		count++;
	}

	// Resetting the count to 0
	count = 0;

	// This loop runs fifty times for each card in their file
	while (count < 50)
	{
		// Generates a random number between 0 and 49
		num = rand() % 50;

		// This runs while the number they randomly chose has not been used
		while (allNums[num] != 0)
		{
			// Gets a new number if the number previously chosen was already used
			num = rand() % 50;
		}
		// Stores the number that hasn't been used into randNums
		randNums[count] = num;

		// Changes the value of allNums so that we know it has been used
		allNums[num] = 1;

		// Incraments counter
		count++;
	}

	// Resets count to 0
	count = 0;

	// This loop runs fifty times for each card in their file
	while (count < 50)
	{
		// Stores the random number into the array passed into the file
		PlayerCards[count] = tempCards[randNums[count]];

		// Incraments count
		count++;
	}
}

// This function is used to pop cards off of the players stack and placing them into the players hand.
void fillHand(stack* playerStack, Card PlayerHand[])
{
	Card* temp;
	for (int count = 0; count < 5; count++)
	{
		// Pops cards off of the stack and places it into an array
		PlayerHand[count] = playerStack->pop();
	}
}

// This function displays all of the players hand
int displayCards(sf::RenderWindow& window, Card playerCard[], sf::Font font, sf::Event event1, int attackOrDefense, queue* attackQueue, queue* defenseQueue)
{
	// creates a new event variable
	sf::Event event2;

	// Completely clears both of the screens
	window.clear();
	window.display();
	window.clear();
	window.display();

	// initializes and deckares a new variable called count to 1
	int count = 1;

	// Creates 4 new queues.
	queue copyAttack1, copyAttack2, copyDefense1, copyDefense2;

	// Displays the queue to the screen
	if (!attackQueue->isEmpty())
	{
		displayQueues(window, attackQueue, defenseQueue);
	}

	// Creating three text variables
	sf::Text enterCardText, attackText, defenseText;

	// setting attributes of the text
	enterCardText.setFillColor(sf::Color::White);
	enterCardText.setFont(font);
	enterCardText.setPosition(950, 1000);
	enterCardText.setCharacterSize(150);

	// Depending on what the user entered it displays attack or defense card.
	if (attackOrDefense == 1)
	{
		enterCardText.setString("Select your Attacking Card: ");
	}
	else
	{
		enterCardText.setString("Select your Defensive Card: ");
	}

	// setting more attributes of sf::string variable
	attackText.setFillColor(sf::Color::White);
	attackText.setFont(font);
	attackText.setPosition(0, 0);
	attackText.setCharacterSize(90);
	attackText.setString("Current Attack:");

	defenseText.setFillColor(sf::Color::White);
	defenseText.setFont(font);
	defenseText.setPosition(3100, 0);
	defenseText.setCharacterSize(90);
	defenseText.setString("Current Defense:");

	// creating an array of integers.
	int cardNumber[5];

	// Putting all the card numbers into the array
	cardNumber[0] = playerCard[0].getCardNum();
	cardNumber[1] = playerCard[1].getCardNum();
	cardNumber[2] = playerCard[2].getCardNum();
	cardNumber[3] = playerCard[3].getCardNum();
	cardNumber[4] = playerCard[4].getCardNum();

	// Creating five new text variables
	sf::Text num1, num2, num3, num4, num5;

	//setting the attributes of num stuff it is only in braces so i can compress it in visual studios
	{
		num1.setString("1");
		num2.setString("2");
		num3.setString("3");
		num4.setString("4");
		num5.setString("5");


		num1.setFillColor(sf::Color::White);
		num1.setPosition(1050, 1820);
		num1.setCharacterSize(120);
		num1.setFont(font);

		num2.setFillColor(sf::Color::White);
		num2.setPosition(1471, 1820);
		num2.setCharacterSize(120);
		num2.setFont(font);

		num3.setFillColor(sf::Color::White);
		num3.setPosition(1892, 1820);
		num3.setCharacterSize(120);
		num3.setFont(font);

		num4.setFillColor(sf::Color::White);
		num4.setPosition(2313, 1820);
		num4.setCharacterSize(120);
		num4.setFont(font);

		num5.setFillColor(sf::Color::White);
		num5.setPosition(2734, 1820);
		num5.setCharacterSize(120);
		num5.setFont(font);
	}

	// creating five new string variables
	string imageFile1, temp, imageFile2, imageFile3, imageFile4, imageFile5;

	// Setting the string to be each monster of their hand
	temp = to_string(cardNumber[0]);
	imageFile1 = "monster" + temp;
	imageFile1 = imageFile1 + ".png";

	temp = to_string(cardNumber[1]);
	imageFile2 = "monster" + temp;
	imageFile2 = imageFile2 + ".png";

	temp = to_string(cardNumber[2]);
	imageFile3 = "monster" + temp;
	imageFile3 = imageFile3 + ".png";

	temp = to_string(cardNumber[3]);
	imageFile4 = "monster" + temp;
	imageFile4 = imageFile4 + ".png";

	temp = to_string(cardNumber[4]);
	imageFile5 = "monster" + temp;
	imageFile5 = imageFile5 + ".png";

	// Creating five rectangle shapes
	sf::RectangleShape card1(sf::Vector2f(421, 614)), card2(sf::Vector2f(421, 614)), card3(sf::Vector2f(421, 614)), card4(sf::Vector2f(421, 614)), card5(sf::Vector2f(421, 614));
	
	// Setting the position of the five cards.
	card1.setPosition(900, 1200);
	card2.setPosition(1321, 1200);
	card3.setPosition(1742, 1200);
	card4.setPosition(2163, 1200);
	card5.setPosition(2584, 1200);

	// Creating five new textures
	sf::Texture Texture1, Texture2, Texture3, Texture4, Texture5;

	// Putting the five textures onto the rectangles
	Texture1.loadFromFile(imageFile1);
	card1.setTexture(&Texture1);

	Texture2.loadFromFile(imageFile2);
	card2.setTexture(&Texture2);

	Texture3.loadFromFile(imageFile3);
	card3.setTexture(&Texture3);

	Texture4.loadFromFile(imageFile4);
	card4.setTexture(&Texture4);

	Texture5.loadFromFile(imageFile5);
	card5.setTexture(&Texture5);

	// Drawing the same stuff onto both windows.
	{
		window.draw(num1);
		window.draw(num2);
		window.draw(num3);
		window.draw(num4);
		window.draw(num5);
		window.draw(card1);
		window.draw(card2);
		window.draw(card3);
		window.draw(card4);
		window.draw(card5);
		window.display();
		window.draw(num1);
		window.draw(num2);
		window.draw(num3);
		window.draw(num4);
		window.draw(num5);
		window.draw(card1);
		window.draw(card2);
		window.draw(card3);
		window.draw(card4);
		window.draw(card5);
		window.display();
	}

	// Creating an integer to check to see if the program is supposed to continue running.
	int x = 0;

	// While loop to run untill the user chooses a card
	while (x < 1)
	{
		// Creates a vector that contains the mouse position
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);

		// Defining an event
		while (window.pollEvent(event2))
		{

		}

		// Logic for choosing which card they chose.

		// If the mouse position is within the rectangle it changes the color to red.
		if (mousePos.x >= 900 && mousePos.x <= 1321 && mousePos.y >= 1200 && mousePos.y <= 1950)
		{
			num1.setFillColor(sf::Color::Color(244, 41, 65));

			// If they click the mouse it returns which card they chose.
			if (event2.type == sf::Event::MouseButtonPressed)
			{
				return 1;
			}
		}
		// If the mouse position isn't within the box it sets the text to white
		else
		{
			num1.setFillColor(sf::Color::White);
		}

		// If the mouse position is within the rectangle it changes the color to red.
		if (mousePos.x >= 1321 && mousePos.x <= 1742 && mousePos.y >= 1200 && mousePos.y <= 1950)
		{
			num2.setFillColor(sf::Color::Color(244, 41, 65));

			// If the mouse position is within the rectangle it changes the color to red.
			if (event2.type == sf::Event::MouseButtonPressed)
			{
				return 2;
			}
		}
		// If the mouse position isn't within the box it sets the text to white
		else
		{
			num2.setFillColor(sf::Color::White);
		}

		// If the mouse position is within the rectangle it changes the color to red.
		if (mousePos.x >= 1742 && mousePos.x <= 2163 && mousePos.y >= 1200 && mousePos.y <= 1950)
		{
			num3.setFillColor(sf::Color::Color(244, 41, 65));

			// If the mouse position is within the rectangle it changes the color to red.
			if (event2.type == sf::Event::MouseButtonPressed)
			{
				return 3;
			}
		}
		// If the mouse position isn't within the box it sets the text to white
		else
		{
			num3.setFillColor(sf::Color::White);
		}

		// If the mouse position is within the rectangle it changes the color to red.
		if (mousePos.x >= 2163 && mousePos.x <= 2584 && mousePos.y >= 1200 && mousePos.y <= 1950)
		{
			num4.setFillColor(sf::Color::Color(244, 41, 65));

			// If the mouse position is within the rectangle it changes the color to red.
			if (event2.type == sf::Event::MouseButtonPressed)
			{
				return 4;
			}
		}
		// If the mouse position isn't within the box it sets the text to white
		else
		{
			num4.setFillColor(sf::Color::White);
		}

		// If the mouse position is within the rectangle it changes the color to red.
		if (mousePos.x >= 2584 && mousePos.x <= 3005 && mousePos.y >= 1200 && mousePos.y <= 1950)
		{
			num5.setFillColor(sf::Color::Color(244, 41, 65));

			// If the mouse position is within the rectangle it changes the color to red.
			if (event2.type == sf::Event::MouseButtonPressed)
			{
				return 5;
			}
		}
		// If the mouse position isn't within the box it sets the text to white
		else
		{
			num5.setFillColor(sf::Color::White);
		}

		// Drawing the same things onto both of the windows
		window.draw(enterCardText);
		window.draw(attackText);
		window.draw(defenseText);
		window.draw(num1);
		window.draw(num2);
		window.draw(num3);
		window.draw(num4);
		window.draw(num5);
		window.display();

		window.draw(enterCardText);
		window.draw(attackText);
		window.draw(defenseText);
		window.draw(num1);
		window.draw(num2);
		window.draw(num3);
		window.draw(num4);
		window.draw(num5);
		window.display();
	}
}

// This function lets the players know who's turn it is and how many life points they have
void startingGameScreen(sf::RenderWindow& window, sf::Event event1, string playerName, sf::Font font, int lifeScreen)
{
	// Clears the screen
	window.clear();

	// Pauses the application for 300 milliseconds
	Sleep(300);

	// Creates three text and one string variable
	sf::Text playerTurn, enterContinue, life;
	string playersTurnString;

	// If the players name is less than 7 characters it makes the size 500
	if (playerName.length() < 7)
	{
		playerTurn.setCharacterSize(500);
	}
	// if the length is longer it makes the char size smaller so it fits on the screen
	else
	{
		playerTurn.setCharacterSize(300);
	}

	// setting all words on the screen to the right font, position, string, and size so it knows where/what to display
	playersTurnString = playerName + "'s Turn";

	playerTurn.setString(playersTurnString);
	playerTurn.setPosition(450, 600);
	playerTurn.setFont(font);

	enterContinue.setString("Enter to Continue...");
	enterContinue.setPosition(3000, 1500);
	enterContinue.setFont(font);
	enterContinue.setCharacterSize(50);

	string tempStrings;
	tempStrings = to_string(lifeScreen);
	tempStrings = tempStrings + " Life Points";

	life.setString(tempStrings);
	life.setPosition(1300, 400);
	life.setFont(font);
	life.setCharacterSize(150);

	// draws all of the variables we made and defined and displays them to the screen
	window.draw(playerTurn);
	window.draw(enterContinue);
	window.draw(life);
	window.display();

	while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		//this just pauses the screen untill they hit enter to continue
	}
}

// This function replace the card the user chose with the next one in the queue
void updateCard(int cardChoice, Card playerHand[], stack* playerStack)
{
	// Dequeues the next card and places it into the correct position based off of what the user inputed.
	playerHand[cardChoice - 1] = playerStack->pop();
}

// This function fills the players stack with the players shuffled array
void fillPlayerStack(stack* playerStack, Card playersCards[])
{
	// This loop runs fifty times. One time for each card the player has
	for (int count = 0; count < 50; count++)
	{
		// Pushes the element of the array that the loop is on into the players stack.
		playerStack->push(playersCards[count]);
	}
}

// This function adds a card from a players hand into a queue
void addToQueue(queue* inQueue, int cardChoice, Card playersHand[])
{
	// Enqueues the desired card from the hand into the inputed queue
	inQueue->enqueue(playersHand[cardChoice - 1]);
}

// This function is used to display the attack and defense queue to the side of the screen.
void displayQueues(sf::RenderWindow& window, queue* attackQueue, queue* defenseQueue)
{
	// setting the initial y poistion to 100 pixels
	int yPos = 100;

	string temp, imageFile;

	// declaring a temporary card
	Card tempCard;

	// creating two queues for storing data in temporarily
	queue tempQueue1, tempQueue2;

	// creating a while loop that runs while there are still cards in the attack queue
	while (!attackQueue->isEmpty())
	{
		// Dequeues a card and stores it in the temporary card
		attackQueue->dequeue(tempCard);

		// Enqueues the card back into a temporary queue so that we can still use that card
		tempQueue1.enqueue(tempCard);

		// Takes the card number from the card and makes it a string
		temp = to_string(tempCard.getCardNum());

		// Makes image file equal to the the correct string so the computer knows which image to load
		imageFile = "monster" + temp;
		imageFile = imageFile + ".png";

		// Creating a new card and texture variable
		sf::RectangleShape card(sf::Vector2f(421, 614));
		sf::Texture Texture1;

		// Loading an image from the file onto the texture
		Texture1.loadFromFile(imageFile);

		// Placing the texture onto the rectangle and setting its position
		card.setTexture(&Texture1);
		card.setPosition(0, yPos);

		// increasing y position so that the cards will not overlap next time
		yPos += 614;

		// draws the card onto both screens
		window.draw(card);
		window.display();
		window.draw(card);
		window.display();
	}
	// This while loop restores the attack queue to what it was at the start of the code
	while (!tempQueue1.isEmpty())
	{
		// Creating a temporary variable with type Card
		Card tempCard;
		
		// dequeues the tempQueue and puts it into the temporary card
		tempQueue1.dequeue(tempCard);

		// enqueues the temporary card back into the attack queue
		attackQueue->enqueue(tempCard);
	}

	// Resets the yPos back to 0 so that when it does the defense queue the cards will place at the right height
	yPos = 100;

	// The following code is exactly the same as the above code except that it is for the defense queue
	while (!defenseQueue->isEmpty())
	{
		defenseQueue->dequeue(tempCard);
		tempQueue2.enqueue(tempCard);
		temp = to_string(tempCard.getCardNum());
		imageFile = "monster" + temp;
		imageFile = imageFile + ".png";

		sf::RectangleShape card(sf::Vector2f(421, 614));
		sf::Texture Texture1;
		Texture1.loadFromFile(imageFile);
		card.setTexture(&Texture1);
		card.setPosition(3400, yPos);
		yPos += 614;

		window.draw(card);
		window.display();
		window.draw(card);
		window.display();
	}
	while (!tempQueue2.isEmpty())
	{
		tempQueue2.dequeue(tempCard);
		defenseQueue->enqueue(tempCard);
	}
}

// This function determines who lost life points each turn.
void gameLogic(queue* p1AttackQueue, queue* p1DefenseQueue, queue* p2AttackQueue, queue* p2DefenseQueue, int* p1Health, int* p2Health)
{
	// Making four temporary card variables
	Card p1Attack, p1Defense, p2Attack, p2Defense;

	// Creating a while loop that runs while all four of the queues aren't empty.
	while (!p1AttackQueue->isEmpty() && !p1DefenseQueue->isEmpty() && !p2AttackQueue->isEmpty() && !p2DefenseQueue->isEmpty())
	{
		// Dequeues all the cards into the temporary cards we defined before
		p1AttackQueue->dequeue(p1Attack);
		p1DefenseQueue->dequeue(p1Defense);
		p1DefenseQueue->dequeue(p1Defense);
		p2AttackQueue->dequeue(p2Attack);
		p2DefenseQueue->dequeue(p2Defense);
		p2DefenseQueue->dequeue(p2Defense);

		// If player ones attack points are higher then the other players defense points then you take the difference away from player 2's health
		if (p1Attack.getAttackPoints() > p2Defense.getDefensePoints())
		{
			*p2Health = *p2Health - (p1Attack.getAttackPoints() - p2Defense.getDefensePoints());
		}
		// If player twos attack points are higher then the other players defense points then you take the difference away from player 1's health
		if (p2Attack.getAttackPoints() > p1Defense.getDefensePoints())
		{
			*p1Health = *p1Health - (p2Attack.getAttackPoints() - p1Defense.getDefensePoints());
		}
	}
}

// This function displays the winner of the game to the screen
void winnerScreen(sf::RenderWindow& window, sf::Font font, string P1Name, string P2Name, int p1LifePoints, int p2LifePoints)
{
	// Clears the screen 
	window.clear();
	window.display();
	window.clear();
	window.display();

	// Creates a rectangle shape
	sf::RectangleShape background;

	// Creating a string that will store the winners name
	string winnerName;

	// If player1's life points are greater than 0 then they're the winner and their name is stored in winner name
	if (p1LifePoints > 0)
	{
		winnerName = P1Name;
	}
	// If player2's life points are greater than 0 then they're the winner and their name is stored in winner name
	else
	{
		winnerName = P2Name;
	}

	winnerName = "The winner is " + winnerName;

	// Creating two text variables
	sf::Text winnerText, returnText;

	// Setting attributes of winner text so that it displays to the screen.
	winnerText.setPosition(sf::Vector2f(400, 750));
	winnerText.setCharacterSize(320);
	winnerText.setFont(font);
	winnerText.setFillColor(sf::Color::White);
	winnerText.setString(winnerName);

	// Creating a new event variable
	sf::Event check;

	// Creating a new vector variable and storing the mouse position.
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);

	// Creating a boolean variable to check if we want to leave
	bool leaveGame = FALSE;
	while (leaveGame != TRUE)
	{
		// initializes the check event to be whatever the user did.
		while (window.pollEvent(check))
		{
		}

		// Checks to see if the user chose to close the window
		if (check.type == sf::Event::Closed)
		{
			// Closes the window
			window.close();

			// Returns to the previous function
			return;
		}

		// Creating a new texture and loading in backArrow.png onto that texture.
		sf::Texture arrowImage;
		arrowImage.loadFromFile("backArrow.png");

		// Creating two rectangle shapes both size 100 by 100 to display an image.
		sf::RectangleShape whiteBackground(sf::Vector2f(100, 100)), backArrow(sf::Vector2f(100, 100));;

		// Setting color of the white rectangle
		whiteBackground.setFillColor(sf::Color::White);

		// Stores the texture onto the rectangle
		backArrow.setTexture(&arrowImage);

		// Creating a new texture variable
		sf::Text returnMenu;

		// Setting all the attributes of the text variable so it can be displayed to the screen properly.
		returnMenu.setString("Return");
		returnMenu.setFont(font);
		returnMenu.setCharacterSize(100);
		returnMenu.setPosition(sf::Vector2f(90, -10));
		returnMenu.setFillColor(sf::Color::White);

		// reassigns the value of check
		window.pollEvent(check);

		// If the mouse position is within a certain rectangle it changes the color of the arrow
		if ((mousePos.x >= 0 && mousePos.x <= 420) && (mousePos.y >= 60 && mousePos.y <= 180))
		{
			// Sets fill color to red. 
			whiteBackground.setFillColor(sf::Color::Color(244, 41, 65));
			returnMenu.setFillColor(sf::Color::Color(244, 41, 65));

			// If the mouse position is in the correct rectangle and they clicked then leave game becomes true.
			if (check.type == sf::Event::MouseButtonPressed)
			{
				leaveGame = TRUE;
			}
		}
		// If the mouse position isnt in the rectangle then it sets the fill color to white.
		else
		{
			whiteBackground.setFillColor(sf::Color::White);
			returnMenu.setFillColor(sf::Color::White);
		}

		// draws the other variables onto the screen and then displays the screen
		window.draw(whiteBackground);
		window.draw(backArrow);
		window.draw(returnMenu);
		window.draw(winnerText);
		window.display();
	}
}