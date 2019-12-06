							***WARNING***
This program may not run in all windows. This is my first program written in SFML and I did not account for changing window sizes.
It is specifically designed to run on a 4k display and may not run on your machine.
							*************

This program was created and written by Michael Larson for an assignment in my CPT_S 122 class at Washington State University
CPT_S 122 is a class that teaches data structures in both C and C++.
This game was written in C++ and it uses arrays, stacks, and queues to store our data.
SFML was utilized for the graphics of our game.

This game was not created to be a mimic of YU-GI-OH so it will not follow the same exact rules as its game.
In this game you login and get your cards; if it is your first time playing you will be generated fifty cards and stored in a file.
If it is not your first time then it will load your cards from a file into an array.
The contents of the array will  be shuffled so you do not get the same cards every time you play.
This array is then pushed onto a stack to resemble a deck.
5 cards get popped off the stack and are entered into the players hand[array].
Player1 will choose an attack card and a defense card. Each card will be added to an attack queue and a defense queue.
The same thing happens for Player2.

Once every player has chosen a card and their cards have been enqueued the "battle" stage commences. 
Player1's attack card is dequeued as well as Player2's defense card. There attack and defense points are compared.
If the attack points of P1 card is higher then the defense points of P2Card. Then P2's lifepoints decrease by the difference.
The same thing then happens but the roles are reversed.

Both Players start out with 8000 life points and when either player reaches zero life points the game is over.


Future of this program/project:
	-Go back and make it work on other computer sizes
		This would require scaling of images and also changing window sizes.

	-Implement trading aspect of game
		This would change the game up more as you could trade cards with other people.
		A lot of code for this is already written I just need to implement it.

	-Adding images behind the player card selection
		Not too difficult I will just have to use photoshop to make a background.

	-Erase chars
		As of this minute if tou try to type somebodys name in but you make a mistake there is no way to erase chars
		I would like to make it so you can actually use the backspace key.

	-Error Checking to make sure they enter a name.

	- Make it so that the types actually do something. i.e multiplers on damage or defense.

	- Make it so that if a card does not "die" it stays in the queue.

	- If you run out of cards whoever has more cards is the winner.

	- Make it so that you can close the window at any point

Unrealistic at this moment but stuff that would be cool to add:
	-Adding animations so the cards "hit" each other
	