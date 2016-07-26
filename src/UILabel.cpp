#include "UILabel.hpp"

UILabel::UILabel()
{
	myText = "";
	mySize = 16;
}

void UILabel::setText(sf::String text)
{
	myText = text;
}

void UILabel::setText(std::string text)
{
	myText = text;
}

void UILabel::setText(char * text)
{
	myText = text;
}

void UILabel::setText(const char * text)
{
	myText = text;
}

void UILabel::setSize(int size)
{
	mySize = size;
}

void UILabel::draw(sf::RenderWindow * window)
{
	sf::Text text(myText, Globals::Font, mySize);
	text.setPosition(myTruePosition.x, myTruePosition.y);
	window->draw(text);
}
