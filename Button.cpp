#include "Button.h"

Button::Button(int x, int y, int width, int heigth, sf::Font &f, sf::Color color) {

	this->x = x;
	this->y = y;
	this->width = width;
	this->heigth = heigth;

	button.setPosition(x, y);
	button.setFillColor(color);
	button.setSize(sf::Vector2f(width, heigth));
	button.setOutlineColor(sf::Color::Black);
	button.setOutlineThickness(2);

	text.setFont(f);
	text.setPosition(x + (width / 2.0), y + (heigth / 2.0));
	text.setFillColor(sf::Color::Black);
	
}

bool Button::isClicked(int mouseX, int mouseY) {
	return (mouseX > x && mouseX < x + width) && (mouseY > y && mouseY < y + heigth);
}

void Button::setText(std::string str, float textW) {
	text.setString(str);
	text.setCharacterSize(textW);
	text.setPosition(x + (width / 2.0) - ((4.5 * textW / 15.0) * str.length()), y + (heigth / 2.0) - (2*textW/3));
}

void Button::toggle() {
	button.setFillColor(sf::Color(button.getFillColor().r, button.getFillColor().g, button.getFillColor().b, 255));
	toggled = true;
}

void Button::release() {
	button.setFillColor(sf::Color(button.getFillColor().r, button.getFillColor().g, button.getFillColor().b, 155));
	toggled = false;
}

void Button::draw(sf::RenderWindow& window) {
	window.draw(button);
	window.draw(text);
}