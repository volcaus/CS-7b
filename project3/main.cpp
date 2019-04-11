#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include "complx.h"

void underConstruction(sf::RenderWindow&); // placeholder function for unfinished menu selections
void textAnimation(sf::Text&, bool&, int&); // self-explanatory
int mainMenu(sf::RenderWindow&, sf::Font&); // looped main menu that calls the following functions
void additionMenu(sf::RenderWindow&, sf::Font&); // Allows playing with the Complx class
void subtractionMenu(sf::RenderWindow&, sf::Font&); // Allows playing with the Complx class
void multiplicationMenu(sf::RenderWindow&, sf::Font&); // Allows playing with the Complx class
void divisionMenu(sf::RenderWindow&, sf::Font&); // Allows playing with the Complx class

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "SFML APP", sf::Style::Close);
	window.setFramerateLimit(60);

	sf::Vector2u screenSize = window.getSize();
	
	sf::Font fnt;
	fnt.loadFromFile("fnt/Sansation-Bold.ttf");

	bool fade = 1; // used for fading animation of text
	int alpha = 250; // as above so below

	sf::Text beginText("PRESS SPACE", fnt, 30);
	sf::FloatRect beginTextRect = beginText.getLocalBounds();
	beginText.setOrigin(beginTextRect.left + beginTextRect.width / 2.0f, // Sets origin of text to the center
		beginTextRect.top + beginTextRect.height / 2.0f);								// of its container

	beginText.setPosition(sf::Vector2f(screenSize.x/2.0f, screenSize.y/2.0f)); // centers text relative to screen


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Space)
				{
					switch (mainMenu(window, fnt)) // Calls mainMenu which returns user selection
					{														// which will call one of the following
					case 0:
						//underConstruction(window);
						additionMenu(window, fnt);
						break;
					case 1:
						underConstruction(window);
						//subtractionMenu(window, fnt);
						break;
					case 2:
						underConstruction(window);
						//multiplicationMenu(window, fnt);
						break;
					case 3:
						underConstruction(window);
						//divisionMenu(window, fnt);
						break;
					case 4:
						window.close();
						break;
					default:
						break;
					}
				}
		}

		textAnimation(beginText, fade, alpha); // Used only for the splash screen text (currently)


		window.clear();
		window.draw(beginText);
		window.display();
	}

	return 0;
}

void textAnimation(sf::Text& text, bool& fade, int& alpha)
{
			if (alpha >= 250)
			fade = 1;

		if (alpha <= 50)
			fade = 0;

		if (fade ==1)
			alpha -= 2;

		else if (fade == 0)
			alpha += 2;

		text.setFillColor(sf::Color(255, 255, 255, alpha));

}

int mainMenu(sf::RenderWindow& window, sf::Font& fnt)
{
	int selection = 0;
	bool quit = 0;
	sf::Event menuEvent;

	while (!quit)
	{
		std::vector<sf::Text> menu (5, sf::Text ("Option", fnt, 30)); 
		// Vector of sf::Text objects for the main menu
		
		sf::Vector2u screenSize = window.getSize(); // getting size of window again in case of a resize

	/* The following proccess will be used repeatedly in order to set the origin
		of certain elements to the center of their bounds. Essentially you create 
		a rect with the bounds of the object whose origin you want centered. 
		You can use those values to offset  the origin of said object.
	*/

		sf::FloatRect menuRect (sf::Vector2f(screenSize.x - screenSize.x,
			screenSize.y - (2*screenSize.y)/3), sf::Vector2f(screenSize.x, screenSize.y/3));
	
	menu[0].setString("Addition"); // Setting the text per Text object
	menu[1].setString("Subtraction");
	menu[2].setString("Multiplication");
	menu[3].setString("Division");
	menu[4].setString("Quit");

	sf::FloatRect textRect0 = menu[0].getLocalBounds(); // Now that the Text objects have the desired
	sf::FloatRect textRect1 = menu[1].getLocalBounds(); // strings we can construct the rects as described above
	sf::FloatRect textRect2 = menu[2].getLocalBounds(); // because they now have their final size/bounds
	sf::FloatRect textRect3 = menu[3].getLocalBounds();
	sf::FloatRect textRect4 = menu[4].getLocalBounds();

	menu[0].setOrigin(textRect0.left + textRect0.width/2.0f, textRect0.top + textRect0.height/2.0f);
	menu[0].setPosition(sf::Vector2f(screenSize.x/4, menuRect.top + menuRect.top/6));
	menu[1].setOrigin(textRect1.left + textRect1.width/2.0f, textRect1.top + textRect1.height/2.0f);
	menu[1].setPosition(sf::Vector2f(3*screenSize.x/4, menuRect.top + menuRect.top/6));
	menu[2].setOrigin(textRect2.left + textRect2.width/2.0f, textRect2.top + textRect2.height/2.0f);
	menu[2].setPosition(sf::Vector2f(screenSize.x/4, menuRect.top + menuRect.top/2));
	menu[3].setOrigin(textRect3.left + textRect3.width/2.0f, textRect3.top + textRect3.height/2.0f);
	menu[3].setPosition(sf::Vector2f(3*screenSize.x/4, menuRect.top + menuRect.top/2));
	menu[4].setOrigin(textRect4.left + textRect4.width/2.0f, textRect4.top + textRect4.height/2.0f);
	menu[4].setPosition(sf::Vector2f(screenSize.x/2, menuRect.top + (5*menuRect.top/6)));

	/* 
		The following loop is used to check for user input.
		The options are aligned in 2 columns with each
		option reffered to by an "int selection" value.
		The top left option is 0, moving left to right and top to bottom
		each move should ellicit a selection++. Any selection immediately 
		below a selection, n, will be n+2. So a keypress of down ellicits
		a selection += 2, and a keypress of up, selection -= 2.
	*/

	while (window.pollEvent(menuEvent))
	{
		if (menuEvent.type == sf::Event::KeyPressed)
		{
			if (menuEvent.key.code == sf::Keyboard::Right)
			{
				selection++;
				if (selection >= 4) // max selection is currently 4
					selection = 4;
			}
			if (menuEvent.key.code  == sf::Keyboard::Left)
			{
				selection--;
				if (selection <= 0) // min selection is always 0
					selection = 0;
			}
			if (menuEvent.key.code == sf::Keyboard::Down)
			{
				selection += 2;
				if (selection >= 4) // max selection is currently 4
					selection = 4;
			}
			if (menuEvent.key.code  == sf::Keyboard::Up)
			{
				selection -= 2;
				if (selection <= 0) // min selection is always 0
					selection = 0;
			}
			if(menuEvent.key.code == sf::Keyboard::Space) // pressing space returns the hovered
				return selection;													// selections int value
		}
	}

	for (sf::Text i : menu)	// sets all text to white
		i.setFillColor(sf::Color::White);

	menu[selection].setFillColor(sf::Color::Red); // but this then sets hovered selection to red

	window.clear();
	for (sf::Text i : menu) // draws all text objects in the vector
		window.draw(i);

	window.display();
	}

	return selection;
}

void underConstruction(sf::RenderWindow& window)
{
	sf::Font fnt;
	sf::Vector2u screenSize = window.getSize();
	fnt.loadFromFile("fnt/Sansation-Bold.ttf");

	sf::Text text("UNDER CONSTRUCTION", fnt, 30);
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
							textRect.top + textRect.height / 2.0f);
	text.setPosition(sf::Vector2f(screenSize.x/2.0f, screenSize.y/2.0f));

}

void additionMenu(sf::RenderWindow& window, sf::Font& fnt)
{
	bool quit = 0;
	int selection = 0;
	std::string str = "";


	while(!quit)
	{
		sf::Event addEvent;
		sf::Vector2u screenSize = window.getSize();
		sf::RectangleShape textBox(sf::Vector2f(3*screenSize.x/4, screenSize.y/12));
		sf::Text input(str, fnt, 20U);
		input.setFillColor(sf::Color::Red);

		textBox.setFillColor(sf::Color::White);
		textBox.setOrigin(sf::Vector2f(textBox.getSize().x/2, textBox.getSize().y/2));
		textBox.setPosition(sf::Vector2f(screenSize.x/2, screenSize.y/2));

		input.setOrigin(sf::Vector2f(input.getScale().x/2,input.getScale().y/2));
		input.setPosition(screenSize.x/2,screenSize.y/2);

		while (window.pollEvent(addEvent))
		{
			if (addEvent.type == sf::Event::KeyPressed)
			{
				if (addEvent.key.code == sf::Keyboard::Down)
				{
					selection += 1;
					if (selection > 1)
						selection = 1;
				}
				else if(addEvent.key.code == sf::Keyboard::Up)
				{
					selection -= 1;
					if (selection < 0)
						selection = 0;
				}
			}
			if (addEvent.type == sf::Event::TextEntered)
			{
				if (addEvent.text.unicode == 8 && !str.empty())
					str.pop_back();
				if (addEvent.text.unicode < 128 && isalpha(static_cast<char>(addEvent.text.unicode)))
				{
					str += static_cast<char>(addEvent.text.unicode);
					input.setString(str);
				}
			}
		}



	window.clear();
	window.draw(textBox);
	window.draw(input);
	window.display();
	}
}