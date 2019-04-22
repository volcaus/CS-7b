/* @Author - John Beresford
* @Assignment - SFML Complex Numbers and Basins of Attraction
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <regex>
#include "complx.h"

void textAnimation(sf::Text&, bool&, int&); // self-explanatory

int mainMenu(sf::RenderWindow&, sf::Font&); // looped main menu that calls the following functions
void additionMenu(sf::RenderWindow&, sf::Font&); // Allows playing with the Complx class
void subtractionMenu(sf::RenderWindow&, sf::Font&); // Allows playing with the Complx class
void multiplicationMenu(sf::RenderWindow&, sf::Font&); // Allows playing with the Complx class
void divisionMenu(sf::RenderWindow&, sf::Font&); // Allows playing with the Complx class
void basins(sf::RenderWindow&, sf::Font); // displays the basins of attraction

Complx addComplx(std::string); // adds 2 Complx #'s
Complx subComplx(std::string); // subtracts 2 Complx #'s
Complx mulComplx(std::string); // multiplies 2 Complx #'s
Complx divComplx(std::string); // divides 2 Complx #'s
int babylonianAlgorithm(Complx);

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "SFML APP", sf::Style::Close || sf::Style::Resize);

	sf::Vector2u screenSize = window.getSize();

	sf::Font fnt;
	fnt.loadFromFile("fnt/sansation.ttf");

	bool fade = 1; // used for fading animation of text
	int alpha = 250; // as above so below

	sf::Text beginText("PRESS SPACE", fnt, 30);
	sf::FloatRect beginTextRect = beginText.getLocalBounds();
	beginText.setOrigin(beginTextRect.left + beginTextRect.width / 2.0f, // Sets origin of text to the center
		beginTextRect.top + beginTextRect.height / 2.0f);								// of its container

	beginText.setPosition(sf::Vector2f(screenSize.x / 2.0f, screenSize.y / 2.0f)); // centers text relative to screen


	while (window.isOpen())
	{
		window.setFramerateLimit(60);
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
						additionMenu(window, fnt);
						break;
					case 1:
						subtractionMenu(window, fnt);
						break;
					case 2:
						multiplicationMenu(window, fnt);
						break;
					case 3:
						divisionMenu(window, fnt);
						break;
					case 4:
						window.clear();
						window.display();
						basins(window, fnt);
						break;
					case 5:
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

	if (fade == 1)
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
		std::vector<sf::Text> menu(6, sf::Text("Option", fnt, 30));
		// Vector of sf::Text objects for the main menu

		sf::Vector2u screenSize = window.getSize(); // getting size of window again in case of a resize

													/* The following proccess will be used repeatedly in order to set the origin
													of certain elements to the center of their bounds. Essentially you create
													a rect with the bounds of the object whose origin you want centered.
													You can use those values to offset  the origin of said object.
													*/

		sf::FloatRect menuRect(sf::Vector2f(screenSize.x - screenSize.x,
			screenSize.y - (2 * screenSize.y) / 3), sf::Vector2f(screenSize.x, screenSize.y / 3));

		menu[0].setString("Addition"); // Setting the text per Text object
		menu[1].setString("Subtraction");
		menu[2].setString("Multiplication");
		menu[3].setString("Division");
		menu[4].setString("Basins");
		menu[5].setString("Quit");

		sf::FloatRect textRect0 = menu[0].getLocalBounds(); // Now that the Text objects have the desired
		sf::FloatRect textRect1 = menu[1].getLocalBounds(); // strings we can construct the rects as described above
		sf::FloatRect textRect2 = menu[2].getLocalBounds(); // because they now have their final size/bounds
		sf::FloatRect textRect3 = menu[3].getLocalBounds();
		sf::FloatRect textRect4 = menu[4].getLocalBounds();
		sf::FloatRect textRect5 = menu[5].getLocalBounds();

		menu[0].setOrigin(textRect0.left + textRect0.width / 2.0f, textRect0.top + textRect0.height / 2.0f);
		menu[0].setPosition(sf::Vector2f(screenSize.x / 4, menuRect.top + menuRect.top / 6));
		menu[1].setOrigin(textRect1.left + textRect1.width / 2.0f, textRect1.top + textRect1.height / 2.0f);
		menu[1].setPosition(sf::Vector2f(3 * screenSize.x / 4, menuRect.top + menuRect.top / 6));
		menu[2].setOrigin(textRect2.left + textRect2.width / 2.0f, textRect2.top + textRect2.height / 2.0f);
		menu[2].setPosition(sf::Vector2f(screenSize.x / 4, menuRect.top + menuRect.top / 2));
		menu[3].setOrigin(textRect3.left + textRect3.width / 2.0f, textRect3.top + textRect3.height / 2.0f);
		menu[3].setPosition(sf::Vector2f(3 * screenSize.x / 4, menuRect.top + menuRect.top / 2));
		menu[4].setOrigin(textRect4.left + textRect4.width / 2.0f, textRect4.top + textRect4.height / 2.0f);
		menu[4].setPosition(sf::Vector2f(screenSize.x / 4, menuRect.top + (5 * menuRect.top / 6)));
		menu[5].setOrigin(textRect5.left + textRect5.width / 2.0f, textRect5.top + textRect5.height / 2.0f);
		menu[5].setPosition(sf::Vector2f(3 * screenSize.x / 4, menuRect.top + (5 * menuRect.top / 6)));

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
					if (selection >= 5) // max selection is currently 4
						selection = 5;
				}
				if (menuEvent.key.code == sf::Keyboard::Left)
				{
					selection--;
					if (selection <= 0) // min selection is always 0
						selection = 0;
				}
				if (menuEvent.key.code == sf::Keyboard::Down)
				{
					selection += 2;
					if (selection >= 5) // max selection is currently 4
						selection = 5;
				}
				if (menuEvent.key.code == sf::Keyboard::Up)
				{
					selection -= 2;
					if (selection <= 0) // min selection is always 0
						selection = 0;
				}
				if (menuEvent.key.code == sf::Keyboard::Space) // pressing space returns the hovered
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

void additionMenu(sf::RenderWindow& window, sf::Font& fnt)
{
	bool quit = 0;
	int selection = 0; // Used for traversing the menu GUI
	Complx cnum;

	// This regular expression takes an addition expression in terms of 2 complex #'s
	std::regex regx("^\\s*\\(?\\d+[+]\\d*[i]?\\)?\\s?[+]\\s?\\(?\\d+[+]\\d*[i]?\\)?\\s*$");

	// Used to detect user input
	sf::Event addEvent;

	// Used to hold user input
	std::string str;
	std::stringstream sstr;
	sstr.str("");
	sstr.clear();

	sf::Vector2u screenSize = window.getSize();
	sf::Text header("Enter an expression in the form: (a+bi) + (c+di)", fnt, 23U);
	sf::RectangleShape textBox(sf::Vector2f(3 * screenSize.x / 4, screenSize.y / 12));
	sf::RectangleShape quitButton(sf::Vector2f(3 * screenSize.x / 10, screenSize.y / 12));
	sf::RectangleShape submitButton(sf::Vector2f(3 * screenSize.x / 10, screenSize.y / 12));
	sf::Text submitText("SUBMIT", fnt, 20U);
	sf::Text quitText("BACK", fnt, 20U);
	sf::Text input(str, fnt, 20U);


	while (!quit)
	{
		// Most of the following is inside the main loop in case of a window re-size
		screenSize = window.getSize();
		textBox.setSize(sf::Vector2f(3 * screenSize.x / 4, screenSize.y / 12));
		quitButton.setSize(sf::Vector2f(3 * screenSize.x / 10, screenSize.y / 12));
		submitButton.setSize(sf::Vector2f(3 * screenSize.x / 10, screenSize.y / 12));
		input.setString(str);
		sf::FloatRect headerRect(header.getLocalBounds());
		sf::FloatRect textRect(input.getLocalBounds());
		sf::FloatRect quitRect(quitText.getLocalBounds());
		sf::FloatRect submitRect(submitText.getLocalBounds());
		header.setStyle(sf::Text::Style::Bold);
		header.setFillColor(sf::Color::White);
		input.setFillColor(sf::Color::Black);
		quitText.setFillColor(sf::Color::Black);
		submitText.setFillColor(sf::Color::Black);

		// Setting the positions of the rectangle objects
		textBox.setOrigin(sf::Vector2f(textBox.getSize().x / 2, textBox.getSize().y / 2));
		textBox.setPosition(sf::Vector2f(screenSize.x / 2, screenSize.y / 2));

		submitButton.setOrigin(sf::Vector2f(submitButton.getSize().x / 2, submitButton.getSize().y / 2));
		submitButton.setPosition(sf::Vector2f(screenSize.x / 3, 2 * screenSize.y / 3));

		quitButton.setOrigin(sf::Vector2f(quitButton.getSize().x / 2, quitButton.getSize().y / 2));
		quitButton.setPosition(sf::Vector2f(2 * screenSize.x / 3, 2 * screenSize.y / 3));

		// Aforementioned text-centering protocol
		header.setOrigin(headerRect.left + headerRect.width / 2.0f,
			headerRect.top + headerRect.height / 2.0f);

		input.setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);

		quitText.setOrigin(quitRect.left + quitRect.width / 2.0f,
			quitRect.top + quitRect.height / 2.0f);

		submitText.setOrigin(submitRect.left + submitRect.width / 2.0f,
			submitRect.top + submitRect.height / 2.0f);

		// Setting the position of text objects
		header.setPosition(screenSize.x / 2.0f, screenSize.y / 3.0f);
		input.setPosition(screenSize.x / 2, screenSize.y / 2);
		submitText.setPosition(screenSize.x / 3, 2 * screenSize.y / 3);
		quitText.setPosition(2 * screenSize.x / 3, 2 * screenSize.y / 3);

		// This entire loop is for user input by keyboard
		while (window.pollEvent(addEvent))
		{
			if (addEvent.type == sf::Event::KeyPressed)
			{
				if (addEvent.key.code == sf::Keyboard::Down || addEvent.key.code == sf::Keyboard::Right)
				{
					selection += 1;
					if (selection > 2)
						selection = 2;
				}
				else if (addEvent.key.code == sf::Keyboard::Up || addEvent.key.code == sf::Keyboard::Left)
				{
					selection -= 1;
					if (selection < 0)
						selection = 0;
				}
				else if (addEvent.key.code == sf::Keyboard::Space || addEvent.key.code == sf::Keyboard::Enter)
				{
					switch (selection)
					{
					case 0:
						break;
					case 1:
						if (!regex_match(str, regx))
						{
							str = "Incorrect form";
							break;
						}
						else if (regex_match(str, regx))
						{
							cnum = addComplx(str);
							sstr << cnum;
							str = sstr.str();
							break;
						}
					case 2:
						quit = 1;
						break;
					default:
						break;
					}
				}
			}
			// This will take any unicode character input by the user and append it (barring a backspace)
			// to the input std::string as long as if fits the character criteria (ASCII 32-127)
			if (addEvent.type == sf::Event::TextEntered && selection == 0)
			{
				if (addEvent.text.unicode == 8 && !str.empty())
				{
					sstr.str("");
					sstr.clear();
					str.pop_back();
				}
				if (addEvent.text.unicode < 128 && addEvent.text.unicode > 31)
				{
					str += static_cast<char>(addEvent.text.unicode);
					input.setString(str);
				}
			}
		}

		// Colorizes the text box and buttons as per what is selected
		switch (selection)
		{
		case 0:
			textBox.setFillColor(sf::Color::White);
			submitButton.setFillColor(sf::Color(125, 125, 125, 255));
			quitButton.setFillColor(sf::Color(125, 125, 125, 255));
			break;
		case 1:
			textBox.setFillColor(sf::Color(125, 125, 125, 255));
			submitButton.setFillColor(sf::Color::Red);
			quitButton.setFillColor(sf::Color(125, 125, 125, 255));
			break;
		case 2:
			textBox.setFillColor(sf::Color(125, 125, 125, 255));
			submitButton.setFillColor(sf::Color(125, 125, 125, 255));
			quitButton.setFillColor(sf::Color::Red);
		}



		window.clear();
		window.draw(textBox);
		window.draw(header);
		window.draw(quitButton);
		window.draw(submitButton);
		window.draw(input);
		window.draw(submitText);
		window.draw(quitText);
		window.display();
	}
}

void subtractionMenu(sf::RenderWindow& window, sf::Font& fnt)
{
	bool quit = 0;
	int selection = 0; // Used for traversing the menu GUI
	Complx cnum;

	// This regular expression takes an addition expression in terms of 2 complex #'s
	std::regex regx("^\\s*\\(?\\d+[+]\\d*[i]?\\)?\\s?[-]\\s?\\(?\\d+[+]\\d*[i]?\\)?\\s*$");

	// Used to detect user input
	sf::Event addEvent;

	// Used to hold user input
	std::string str;
	std::stringstream sstr;
	sstr.str("");
	sstr.clear();

	sf::Vector2u screenSize = window.getSize();
	sf::Text header("Enter an expression in the form: (a+bi) - (c+di)", fnt, 23U);
	sf::RectangleShape textBox(sf::Vector2f(3 * screenSize.x / 4, screenSize.y / 12));
	sf::RectangleShape quitButton(sf::Vector2f(3 * screenSize.x / 10, screenSize.y / 12));
	sf::RectangleShape submitButton(sf::Vector2f(3 * screenSize.x / 10, screenSize.y / 12));
	sf::Text submitText("SUBMIT", fnt, 20U);
	sf::Text quitText("BACK", fnt, 20U);
	sf::Text input(str, fnt, 20U);


	while (!quit)
	{
		// Most of the following is inside the main loop in case of a window re-size
		screenSize = window.getSize();
		textBox.setSize(sf::Vector2f(3 * screenSize.x / 4, screenSize.y / 12));
		quitButton.setSize(sf::Vector2f(3 * screenSize.x / 10, screenSize.y / 12));
		submitButton.setSize(sf::Vector2f(3 * screenSize.x / 10, screenSize.y / 12));
		input.setString(str);
		sf::FloatRect headerRect(header.getLocalBounds());
		sf::FloatRect textRect(input.getLocalBounds());
		sf::FloatRect quitRect(quitText.getLocalBounds());
		sf::FloatRect submitRect(submitText.getLocalBounds());
		header.setStyle(sf::Text::Style::Bold);
		header.setFillColor(sf::Color::White);
		input.setFillColor(sf::Color::Black);
		quitText.setFillColor(sf::Color::Black);
		submitText.setFillColor(sf::Color::Black);

		// Setting the positions of the rectangle objects
		textBox.setOrigin(sf::Vector2f(textBox.getSize().x / 2, textBox.getSize().y / 2));
		textBox.setPosition(sf::Vector2f(screenSize.x / 2, screenSize.y / 2));

		submitButton.setOrigin(sf::Vector2f(submitButton.getSize().x / 2, submitButton.getSize().y / 2));
		submitButton.setPosition(sf::Vector2f(screenSize.x / 3, 2 * screenSize.y / 3));

		quitButton.setOrigin(sf::Vector2f(quitButton.getSize().x / 2, quitButton.getSize().y / 2));
		quitButton.setPosition(sf::Vector2f(2 * screenSize.x / 3, 2 * screenSize.y / 3));

		// Aforementioned text-centering protocol
		header.setOrigin(headerRect.left + headerRect.width / 2.0f,
			headerRect.top + headerRect.height / 2.0f);

		input.setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);

		quitText.setOrigin(quitRect.left + quitRect.width / 2.0f,
			quitRect.top + quitRect.height / 2.0f);

		submitText.setOrigin(submitRect.left + submitRect.width / 2.0f,
			submitRect.top + submitRect.height / 2.0f);

		// Setting the position of text objects
		header.setPosition(screenSize.x / 2.0f, screenSize.y / 3.0f);
		input.setPosition(screenSize.x / 2, screenSize.y / 2);
		submitText.setPosition(screenSize.x / 3, 2 * screenSize.y / 3);
		quitText.setPosition(2 * screenSize.x / 3, 2 * screenSize.y / 3);

		// This entire loop is for user input by keyboard
		while (window.pollEvent(addEvent))
		{
			if (addEvent.type == sf::Event::KeyPressed)
			{
				if (addEvent.key.code == sf::Keyboard::Down || addEvent.key.code == sf::Keyboard::Right)
				{
					selection += 1;
					if (selection > 2)
						selection = 2;
				}
				else if (addEvent.key.code == sf::Keyboard::Up || addEvent.key.code == sf::Keyboard::Left)
				{
					selection -= 1;
					if (selection < 0)
						selection = 0;
				}
				else if (addEvent.key.code == sf::Keyboard::Space || addEvent.key.code == sf::Keyboard::Enter)
				{
					switch (selection)
					{
					case 0:
						break;
					case 1:
						if (!regex_match(str, regx))
						{
							str = "Incorrect form";
							break;
						}
						else if (regex_match(str, regx))
						{
							cnum = subComplx(str);
							sstr << cnum;
							str = sstr.str();
							break;
						}
					case 2:
						quit = 1;
						break;
					default:
						break;
					}
				}
			}
			// This will take any unicode character input by the user and append it (barring a backspace)
			// to the input std::string as long as if fits the character criteria (ASCII 32-127)
			if (addEvent.type == sf::Event::TextEntered && selection == 0)
			{
				if (addEvent.text.unicode == 8 && !str.empty())
				{
					sstr.str("");
					sstr.clear();
					str.pop_back();
				}
				if (addEvent.text.unicode < 128 && addEvent.text.unicode > 31)
				{
					str += static_cast<char>(addEvent.text.unicode);
					input.setString(str);
				}
			}
		}

		// Colorizes the text box and buttons as per what is selected
		switch (selection)
		{
		case 0:
			textBox.setFillColor(sf::Color::White);
			submitButton.setFillColor(sf::Color(125, 125, 125, 255));
			quitButton.setFillColor(sf::Color(125, 125, 125, 255));
			break;
		case 1:
			textBox.setFillColor(sf::Color(125, 125, 125, 255));
			submitButton.setFillColor(sf::Color::Red);
			quitButton.setFillColor(sf::Color(125, 125, 125, 255));
			break;
		case 2:
			textBox.setFillColor(sf::Color(125, 125, 125, 255));
			submitButton.setFillColor(sf::Color(125, 125, 125, 255));
			quitButton.setFillColor(sf::Color::Red);
		}



		window.clear();
		window.draw(textBox);
		window.draw(header);
		window.draw(quitButton);
		window.draw(submitButton);
		window.draw(input);
		window.draw(submitText);
		window.draw(quitText);
		window.display();
	}
}

void multiplicationMenu(sf::RenderWindow& window, sf::Font& fnt)
{
	bool quit = 0;
	int selection = 0; // Used for traversing the menu GUI
	Complx cnum;

	// This regular expression takes an addition expression in terms of 2 complex #'s
	std::regex regx("^\\s*\\(?\\d+[+]\\d*[i]?\\)?\\s?[*]\\s?\\(?\\d+[+]\\d*[i]?\\)?\\s*$");

	// Used to detect user input
	sf::Event addEvent;

	// Used to hold user input
	std::string str;
	std::stringstream sstr;
	sstr.str("");
	sstr.clear();

	sf::Vector2u screenSize = window.getSize();
	sf::Text header("Enter an expression in the form: (a+bi) * (c+di)", fnt, 23U);
	sf::RectangleShape textBox(sf::Vector2f(3 * screenSize.x / 4, screenSize.y / 12));
	sf::RectangleShape quitButton(sf::Vector2f(3 * screenSize.x / 10, screenSize.y / 12));
	sf::RectangleShape submitButton(sf::Vector2f(3 * screenSize.x / 10, screenSize.y / 12));
	sf::Text submitText("SUBMIT", fnt, 20U);
	sf::Text quitText("BACK", fnt, 20U);
	sf::Text input(str, fnt, 20U);


	while (!quit)
	{
		// Most of the following is inside the main loop in case of a window re-size
		screenSize = window.getSize();
		textBox.setSize(sf::Vector2f(3 * screenSize.x / 4, screenSize.y / 12));
		quitButton.setSize(sf::Vector2f(3 * screenSize.x / 10, screenSize.y / 12));
		submitButton.setSize(sf::Vector2f(3 * screenSize.x / 10, screenSize.y / 12));
		input.setString(str);
		sf::FloatRect headerRect(header.getLocalBounds());
		sf::FloatRect textRect(input.getLocalBounds());
		sf::FloatRect quitRect(quitText.getLocalBounds());
		sf::FloatRect submitRect(submitText.getLocalBounds());
		header.setStyle(sf::Text::Style::Bold);
		header.setFillColor(sf::Color::White);
		input.setFillColor(sf::Color::Black);
		quitText.setFillColor(sf::Color::Black);
		submitText.setFillColor(sf::Color::Black);

		// Setting the positions of the rectangle objects
		textBox.setOrigin(sf::Vector2f(textBox.getSize().x / 2, textBox.getSize().y / 2));
		textBox.setPosition(sf::Vector2f(screenSize.x / 2, screenSize.y / 2));

		submitButton.setOrigin(sf::Vector2f(submitButton.getSize().x / 2, submitButton.getSize().y / 2));
		submitButton.setPosition(sf::Vector2f(screenSize.x / 3, 2 * screenSize.y / 3));

		quitButton.setOrigin(sf::Vector2f(quitButton.getSize().x / 2, quitButton.getSize().y / 2));
		quitButton.setPosition(sf::Vector2f(2 * screenSize.x / 3, 2 * screenSize.y / 3));

		// Aforementioned text-centering protocol
		header.setOrigin(headerRect.left + headerRect.width / 2.0f,
			headerRect.top + headerRect.height / 2.0f);

		input.setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);

		quitText.setOrigin(quitRect.left + quitRect.width / 2.0f,
			quitRect.top + quitRect.height / 2.0f);

		submitText.setOrigin(submitRect.left + submitRect.width / 2.0f,
			submitRect.top + submitRect.height / 2.0f);

		// Setting the position of text objects
		header.setPosition(screenSize.x / 2.0f, screenSize.y / 3.0f);
		input.setPosition(screenSize.x / 2, screenSize.y / 2);
		submitText.setPosition(screenSize.x / 3, 2 * screenSize.y / 3);
		quitText.setPosition(2 * screenSize.x / 3, 2 * screenSize.y / 3);

		// This entire loop is for user input by keyboard
		while (window.pollEvent(addEvent))
		{
			if (addEvent.type == sf::Event::KeyPressed)
			{
				if (addEvent.key.code == sf::Keyboard::Down || addEvent.key.code == sf::Keyboard::Right)
				{
					selection += 1;
					if (selection > 2)
						selection = 2;
				}
				else if (addEvent.key.code == sf::Keyboard::Up || addEvent.key.code == sf::Keyboard::Left)
				{
					selection -= 1;
					if (selection < 0)
						selection = 0;
				}
				else if (addEvent.key.code == sf::Keyboard::Space || addEvent.key.code == sf::Keyboard::Enter)
				{
					switch (selection)
					{
					case 0:
						break;
					case 1:
						if (!regex_match(str, regx))
						{
							str = "Incorrect form";
							break;
						}
						else if (regex_match(str, regx))
						{
							cnum = mulComplx(str);
							sstr << cnum;
							str = sstr.str();
							break;
						}
					case 2:
						quit = 1;
						break;
					default:
						break;
					}
				}
			}
			// This will take any unicode character input by the user and append it (barring a backspace)
			// to the input std::string as long as if fits the character criteria (ASCII 32-127)
			if (addEvent.type == sf::Event::TextEntered && selection == 0)
			{
				if (addEvent.text.unicode == 8 && !str.empty())
				{
					sstr.str("");
					sstr.clear();
					str.pop_back();
				}
				if (addEvent.text.unicode < 128 && addEvent.text.unicode > 31)
				{
					str += static_cast<char>(addEvent.text.unicode);
					input.setString(str);
				}
			}
		}

		// Colorizes the text box and buttons as per what is selected
		switch (selection)
		{
		case 0:
			textBox.setFillColor(sf::Color::White);
			submitButton.setFillColor(sf::Color(125, 125, 125, 255));
			quitButton.setFillColor(sf::Color(125, 125, 125, 255));
			break;
		case 1:
			textBox.setFillColor(sf::Color(125, 125, 125, 255));
			submitButton.setFillColor(sf::Color::Red);
			quitButton.setFillColor(sf::Color(125, 125, 125, 255));
			break;
		case 2:
			textBox.setFillColor(sf::Color(125, 125, 125, 255));
			submitButton.setFillColor(sf::Color(125, 125, 125, 255));
			quitButton.setFillColor(sf::Color::Red);
		}



		window.clear();
		window.draw(textBox);
		window.draw(header);
		window.draw(quitButton);
		window.draw(submitButton);
		window.draw(input);
		window.draw(submitText);
		window.draw(quitText);
		window.display();
	}
}

void divisionMenu(sf::RenderWindow& window, sf::Font& fnt)
{
	bool quit = 0;
	int selection = 0; // Used for traversing the menu GUI
	Complx cnum;

	// This regular expression takes an addition expression in terms of 2 complex #'s
	std::regex regx("^\\s*\\(?\\d+[+]\\d*[i]?\\)?\\s?[/]\\s?\\(?\\d+[+]\\d*[i]?\\)?\\s*$");

	// Used to detect user input
	sf::Event addEvent;

	// Used to hold user input
	std::string str;
	std::stringstream sstr;
	sstr.str("");
	sstr.clear();

	sf::Vector2u screenSize = window.getSize();
	sf::Text header("Enter an expression in the form: (a+bi) / (c+di)", fnt, 23U);
	sf::RectangleShape textBox(sf::Vector2f(3 * screenSize.x / 4, screenSize.y / 12));
	sf::RectangleShape quitButton(sf::Vector2f(3 * screenSize.x / 10, screenSize.y / 12));
	sf::RectangleShape submitButton(sf::Vector2f(3 * screenSize.x / 10, screenSize.y / 12));
	sf::Text submitText("SUBMIT", fnt, 20U);
	sf::Text quitText("BACK", fnt, 20U);
	sf::Text input(str, fnt, 20U);


	while (!quit)
	{
		// Most of the following is inside the main loop in case of a window re-size
		screenSize = window.getSize();
		textBox.setSize(sf::Vector2f(3 * screenSize.x / 4, screenSize.y / 12));
		quitButton.setSize(sf::Vector2f(3 * screenSize.x / 10, screenSize.y / 12));
		submitButton.setSize(sf::Vector2f(3 * screenSize.x / 10, screenSize.y / 12));
		input.setString(str);
		sf::FloatRect headerRect(header.getLocalBounds());
		sf::FloatRect textRect(input.getLocalBounds());
		sf::FloatRect quitRect(quitText.getLocalBounds());
		sf::FloatRect submitRect(submitText.getLocalBounds());
		header.setStyle(sf::Text::Style::Bold);
		header.setFillColor(sf::Color::White);
		input.setFillColor(sf::Color::Black);
		quitText.setFillColor(sf::Color::Black);
		submitText.setFillColor(sf::Color::Black);

		// Setting the positions of the rectangle objects
		textBox.setOrigin(sf::Vector2f(textBox.getSize().x / 2, textBox.getSize().y / 2));
		textBox.setPosition(sf::Vector2f(screenSize.x / 2, screenSize.y / 2));

		submitButton.setOrigin(sf::Vector2f(submitButton.getSize().x / 2, submitButton.getSize().y / 2));
		submitButton.setPosition(sf::Vector2f(screenSize.x / 3, 2 * screenSize.y / 3));

		quitButton.setOrigin(sf::Vector2f(quitButton.getSize().x / 2, quitButton.getSize().y / 2));
		quitButton.setPosition(sf::Vector2f(2 * screenSize.x / 3, 2 * screenSize.y / 3));

		// Aforementioned text-centering protocol
		header.setOrigin(headerRect.left + headerRect.width / 2.0f,
			headerRect.top + headerRect.height / 2.0f);

		input.setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);

		quitText.setOrigin(quitRect.left + quitRect.width / 2.0f,
			quitRect.top + quitRect.height / 2.0f);

		submitText.setOrigin(submitRect.left + submitRect.width / 2.0f,
			submitRect.top + submitRect.height / 2.0f);

		// Setting the position of text objects
		header.setPosition(screenSize.x / 2.0f, screenSize.y / 3.0f);
		input.setPosition(screenSize.x / 2, screenSize.y / 2);
		submitText.setPosition(screenSize.x / 3, 2 * screenSize.y / 3);
		quitText.setPosition(2 * screenSize.x / 3, 2 * screenSize.y / 3);

		// This entire loop is for user input by keyboard
		while (window.pollEvent(addEvent))
		{
			if (addEvent.type == sf::Event::KeyPressed)
			{
				if (addEvent.key.code == sf::Keyboard::Down || addEvent.key.code == sf::Keyboard::Right)
				{
					selection += 1;
					if (selection > 2)
						selection = 2;
				}
				else if (addEvent.key.code == sf::Keyboard::Up || addEvent.key.code == sf::Keyboard::Left)
				{
					selection -= 1;
					if (selection < 0)
						selection = 0;
				}
				else if (addEvent.key.code == sf::Keyboard::Space || addEvent.key.code == sf::Keyboard::Enter)
				{
					switch (selection)
					{
					case 0:
						break;
					case 1:
						if (!regex_match(str, regx))
						{
							str = "Incorrect form";
							break;
						}
						else if (regex_match(str, regx))
						{
							cnum = divComplx(str);
							sstr << cnum;
							str = sstr.str();
							break;
						}
					case 2:
						quit = 1;
						break;
					default:
						break;
					}
				}
			}
			// This will take any unicode character input by the user and append it (barring a backspace)
			// to the input std::string as long as if fits the character criteria (ASCII 32-127)
			if (addEvent.type == sf::Event::TextEntered && selection == 0)
			{
				if (addEvent.text.unicode == 8 && !str.empty())
				{
					sstr.str("");
					sstr.clear();
					str.pop_back();
				}
				if (addEvent.text.unicode < 128 && addEvent.text.unicode > 31)
				{
					str += static_cast<char>(addEvent.text.unicode);
					input.setString(str);
				}
			}
		}

		// Colorizes the text box and buttons as per what is selected
		switch (selection)
		{
		case 0:
			textBox.setFillColor(sf::Color::White);
			submitButton.setFillColor(sf::Color(125, 125, 125, 255));
			quitButton.setFillColor(sf::Color(125, 125, 125, 255));
			break;
		case 1:
			textBox.setFillColor(sf::Color(125, 125, 125, 255));
			submitButton.setFillColor(sf::Color::Red);
			quitButton.setFillColor(sf::Color(125, 125, 125, 255));
			break;
		case 2:
			textBox.setFillColor(sf::Color(125, 125, 125, 255));
			submitButton.setFillColor(sf::Color(125, 125, 125, 255));
			quitButton.setFillColor(sf::Color::Red);
		}



		window.clear();
		window.draw(textBox);
		window.draw(header);
		window.draw(quitButton);
		window.draw(submitButton);
		window.draw(input);
		window.draw(submitText);
		window.draw(quitText);
		window.display();
	}
}

Complx addComplx(std::string str)
{
	Complx cnum1, cnum2;
	bool isReal = 1;
	int temp1, temp2;
	std::string cstr1, cstr2, realStr, imagStr;

	size_t found = str.find('+');

	cstr1 = str.substr(0, str.find('+', found + 1)); // Splits the string into 2 seperate complex #'s
	cstr2 = str.substr(str.find('+', found + 1) + 1);

	for (char c : cstr1) // Breaks first complex # into real and imaginary portions
	{
		if (isdigit(c) && isReal)
			realStr += c;
		else if (c == '+')
			isReal = 0;
		else if (isdigit(c) && !isReal)
			imagStr += c;
	}

	// Will change incredibly lazy casting to sstream/boost method (if i remember to)
	temp1 = std::stoi(realStr);
	temp2 = std::stoi(imagStr);
	cnum1.real(static_cast<double>(temp1));
	cnum1.imag(static_cast<double>(temp2));

	realStr.clear();
	imagStr.clear();
	isReal = 1;

	for (char c : cstr2)
	{
		if (isdigit(c) && isReal)
			realStr += c;
		else if (c == '+')
			isReal = 0;
		else if (isdigit(c) && !isReal)
			imagStr += c;
	}

	temp1 = std::stoi(realStr);
	temp2 = std::stoi(imagStr);
	cnum2.real(static_cast<double>(temp1));
	cnum2.imag(static_cast<double>(temp2));

	return cnum1 + cnum2;
}

Complx subComplx(std::string str) // Look to addComplx() for documentation (line 898)
{
	Complx cnum1, cnum2;
	bool isReal = 1;
	int temp1, temp2;
	std::string cstr1, cstr2, realStr, imagStr;

	cstr1 = str.substr(0, str.find('-'));
	cstr2 = str.substr(str.find('-'));

	for (char c : cstr1)
	{
		if (isdigit(c) && isReal)
			realStr += c;
		else if (c == '+')
			isReal = 0;
		else if (isdigit(c) && !isReal)
			imagStr += c;
	}

	// Will change incredibly lazy casting to sstream/boost method (if i remember to)
	temp1 = std::stoi(realStr);
	temp2 = std::stoi(imagStr);
	cnum1.real(static_cast<double>(temp1));
	cnum1.imag(static_cast<double>(temp2));

	realStr.clear();
	imagStr.clear();
	isReal = 1;

	for (char c : cstr2)
	{
		if (isdigit(c) && isReal)
			realStr += c;
		else if (c == '+')
			isReal = 0;
		else if (isdigit(c) && !isReal)
			imagStr += c;
	}

	temp1 = std::stoi(realStr);
	temp2 = std::stoi(imagStr);
	cnum2.real(static_cast<double>(temp1));
	cnum2.imag(static_cast<double>(temp2));

	return cnum1 - cnum2;
}

Complx mulComplx(std::string str) // Look to addComplx() for documentation (line 898)
{
	Complx cnum1, cnum2;
	bool isReal = 1;
	int temp1, temp2;
	std::string cstr1, cstr2, realStr, imagStr;

	cstr1 = str.substr(0, str.find('*'));
	cstr2 = str.substr(str.find('*'));

	for (char c : cstr1)
	{
		if (isdigit(c) && isReal)
			realStr += c;
		else if (c == '+')
			isReal = 0;
		else if (isdigit(c) && !isReal)
			imagStr += c;
	}

	// Will change incredibly lazy casting to sstream/boost method (if i remember to)
	temp1 = std::stoi(realStr);
	temp2 = std::stoi(imagStr);
	cnum1.real(static_cast<double>(temp1));
	cnum1.imag(static_cast<double>(temp2));

	realStr.clear();
	imagStr.clear();
	isReal = 1;

	for (char c : cstr2)
	{
		if (isdigit(c) && isReal)
			realStr += c;
		else if (c == '+')
			isReal = 0;
		else if (isdigit(c) && !isReal)
			imagStr += c;
	}

	temp1 = std::stoi(realStr);
	temp2 = std::stoi(imagStr);
	cnum2.real(static_cast<double>(temp1));
	cnum2.imag(static_cast<double>(temp2));

	return cnum1 * cnum2;
}

Complx divComplx(std::string str) // Look to addComplx() for documentation (line 898)
{
	Complx cnum1, cnum2;
	bool isReal = 1;
	int temp1, temp2;
	std::string cstr1, cstr2, realStr, imagStr;

	cstr1 = str.substr(0, str.find('/'));
	cstr2 = str.substr(str.find('/'));

	for (char c : cstr1)
	{
		if (isdigit(c) && isReal)
			realStr += c;
		else if (c == '+')
			isReal = 0;
		else if (isdigit(c) && !isReal)
			imagStr += c;
	}

	// Will change incredibly lazy casting to sstream method (if i remember to)
	temp1 = std::stoi(realStr);
	temp2 = std::stoi(imagStr);
	cnum1.real(static_cast<double>(temp1));
	cnum1.imag(static_cast<double>(temp2));

	realStr.clear();
	imagStr.clear();
	isReal = 1;

	for (char c : cstr2)
	{
		if (isdigit(c) && isReal)
			realStr += c;
		else if (c == '+')
			isReal = 0;
		else if (isdigit(c) && !isReal)
			imagStr += c;
	}

	temp1 = std::stoi(realStr);
	temp2 = std::stoi(imagStr);
	cnum2.real(static_cast<double>(temp1));
	cnum2.imag(static_cast<double>(temp2));

	return cnum1 / cnum2;
}

void basins(sf::RenderWindow& window, sf::Font fnt)
{
	sf::RenderTexture canvas; // Draw to this first so we can clear the RenderWindow properly
	canvas.create(window.getSize().x, window.getSize().y); // Sizing the RenderTexture
	window.setFramerateLimit(0);
	sf::Vector2f windowSize = sf::Vector2f(window.getSize().x, window.getSize().y);
	bool quit = 0;
	size_t widthPen = 0, heightPen = 0; // Literally the location in window to draw (relative to top left)
	int gradient; // Will be used for when the calculation function returns a non-0, non-100 value
	Complx input(-3, 2); // The real,imag value to begin drawing from (on complex plane)

						 // The following values will be able to be user-defined if given time to implement that
	double scale = 1.0, // pixel density of the below rectangle shape for drawing the basins
		minReal = -3.0; // minimum real values to display on 'graph'
		//minImag = -2.0, // likewise for imaginary values
		//maxReal = 1.0,
		//maxImag = 2.0;

	sf::Event basinEvent;
	sf::Text quitText("Press 'q' to quit", fnt, 12u);

	sf::RectangleShape ink; // rectangle of size scaleXscale to be drawn at pen location
	ink.setSize(sf::Vector2f(scale, scale));


	while (!quit)
	{
		windowSize = sf::Vector2f(window.getSize().x, window.getSize().y);

		while (window.pollEvent(basinEvent)) // checks for 'Q' keypress indicating desire to quit
		{
			if (basinEvent.type == sf::Event::KeyPressed)
				if (basinEvent.key.code == sf::Keyboard::Q)
					quit = 1;
		}
				
		if (widthPen <= windowSize.x && heightPen <= windowSize.y)
		{
			if (widthPen >= windowSize.x) // Checks for end of working line
			{
				input.real(minReal);
				input.imag(input.imag() - 4 * scale / windowSize.y); // Reduces the imaginary value of input by a value relative to screensize
				widthPen = 0;
				heightPen += scale; // Moves down the screen one unit
				if (heightPen > windowSize.y) // End case
					continue;
			}

			ink.setPosition(widthPen, heightPen); // Sets a rectangle at the next point

			switch (gradient = babylonianAlgorithm(input))
			{
			case 0:
				ink.setFillColor(sf::Color::Blue);
				break;
			case 100:
				ink.setFillColor(sf::Color::Black);
				break;
			default:
				ink.setFillColor(sf::Color(75 + gradient, 75 + gradient, 75 + gradient));
				break;
			}

			input.real(input.real() + 4 * scale / windowSize.x); // Increases the real value of the input by a value relative to screensize
			widthPen += scale;
		} 

		canvas.draw(ink); // Draws the rectangle to an offscreen texture
		canvas.display(); // Displays said rectangle (off-screen)

		window.clear(); // Necessary action thus the canvas shenanigans
		sf::Sprite canvasSprite(canvas.getTexture()); // Creates a sprite from canvas texture
		window.draw(canvasSprite);
		window.draw(quitText);
		window.display();
	}
}

int babylonianAlgorithm(Complx c)
{
	Complx offset, temp(c.real(), c.imag());
	int behaviour = 0;

	while ((offset - temp).abs() > 0.001)
	{
		++behaviour;
		offset = temp;
		temp = temp * temp + c;

		if ((offset - temp).abs() > 100)
			return 0;

		if (behaviour > 100)
			return 100;
	}

	return behaviour;
}
