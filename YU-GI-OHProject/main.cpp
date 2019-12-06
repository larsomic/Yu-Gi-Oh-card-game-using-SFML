//************************************************************************************************\\
\\																																												   //
//        This .cpp file contains the definition of main this is where the compiler starts and calls all th eother functions         \\
\\																																										  		   //
//************************************************************************************************\\

// including user defined functions that we need
#include "mainHeader.h"
#include "functionHeader.h"

// definition of the main function
int main()
{
	// creates a window the size of the computers screen the window has a title bar that has the name and alsoan exit button
	sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height - 156), "Yu-Gi-Oh", sf::Style::Close | sf::Style::Resize);
	
	// moves the window slightly over so that it looks full screen
	window.setPosition(sf::Vector2i(-12, 0));

	// this calls the function that displays the main menu
	display_menu_to_screen(window);

	// returns 0 to indicate the program ran succesfully
	return 0;
}