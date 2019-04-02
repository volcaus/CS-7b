#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "complx.h"

void underConstruction(sf::RenderWindow&);
void textAnimation(sf::Text&, bool&, int&);
int mainMenu(sf::RenderWindow&, sf::Font);

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "SFML APP", sf::Style::Close | sf::Style::Resize);
	window.setFramerateLimit(60);
//	window.setKeyRepeatEnabled(false);
	sf::Vector2u screenSize = window.getSize();
	sf::Font fnt;
	fnt.loadFromFile("fnt/Sansation-Bold.ttf");
	bool fade = 1;
	int alpha = 250;

	sf::Text beginText("PRESS SPACE", fnt, 30);
	sf::FloatRect beginTextRect = beginText.getLocalBounds();
	beginText.setOrigin(beginTextRect.left + beginTextRect.width / 2.0f,
						beginTextRect.top + beginTextRect.height / 2.0f);
	beginText.setPosition(sf::Vector2f(screenSize.x/2.0f, screenSize.y/2.0f));


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
					switch (mainMenu(window, fnt))
					{
					case 0:
						window.close();
						break;
					case 1:
						underConstruction(window);
						break;
					case 2:
						underConstruction(window);
						break;
					case 3:
						underConstruction(window);
						break;
					case 4:
						underConstruction(window);
						break;
					default:
						break;
					}
				}
		}

		textAnimation(beginText, fade, alpha);


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

int mainMenu(sf::RenderWindow& window, sf::Font fnt)
{
	int selection = 0;
	bool quit = 0;
	sf::Event menuEvent;

	while (!quit)
	{
		std::vector<sf::Text> menu (5, sf::Text ("Option", fnt, 30));
		sf::FloatRect textRect = menu[0].getLocalBounds();
		sf::Vector2u screenSize = window.getSize();

		sf::FloatRect menuRect (sf::Vector2f(screenSize.x - screenSize.x,
													screenSize.y - (2*screenSize.y)/3),
													sf::Vector2f(screenSize.x, screenSize.y/3));

	menu[0].setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
	menu[0].setPosition(sf::Vector2f(screenSize.x/4, menuRect.top + menuRect.top/6));
	menu[1].setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
	menu[1].setPosition(sf::Vector2f(3*screenSize.x/4, menuRect.top + menuRect.top/6));
	menu[2].setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
	menu[2].setPosition(sf::Vector2f(screenSize.x/4, menuRect.top + menuRect.top/2));
	menu[3].setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
	menu[3].setPosition(sf::Vector2f(3*screenSize.x/4, menuRect.top + menuRect.top/2));
	menu[4].setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
	menu[4].setPosition(sf::Vector2f(screenSize.x/2, menuRect.top + (5*menuRect.top/6)));

	while (window.pollEvent(menuEvent))
	{
		if (menuEvent.type == sf::Event::KeyPressed)
		{
			if (menuEvent.key.code == sf::Keyboard::Right)
			{
				selection++;
				if (selection >= 4)
					selection = 4;
			}
			if (menuEvent.key.code  == sf::Keyboard::Left)
			{
				selection--;
				if (selection <= 0)
					selection = 0;
			}
			if (menuEvent.key.code == sf::Keyboard::Down)
			{
				selection += 2;
				if (selection >= 4)
					selection = 4;
			}
			if (menuEvent.key.code  == sf::Keyboard::Up)
			{
				selection -= 2;
				if (selection <= 0)
					selection = 0;
			}
		}
	}

	for (sf::Text i : menu)
		i.setFillColor(sf::Color::White);

	menu[selection].setFillColor(sf::Color::Red);

	window.clear();
	for (sf::Text i : menu)
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
