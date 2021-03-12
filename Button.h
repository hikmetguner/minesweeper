#pragma once
#include <SFML/Graphics.hpp>
class Button
{
public:
	Button(int x, int y, int width, int heigth, sf::Font &f, sf::Color color = sf::Color::White);

	int x, y, heigth, width;
	sf::RectangleShape button;
	sf::Text text;
	bool toggled = false;

	bool isClicked(int mouseX, int mouseY);
	void toggle();
	void release();
	void setText(std::string str, float textW = 36);
	void draw(sf::RenderWindow& window);
};

