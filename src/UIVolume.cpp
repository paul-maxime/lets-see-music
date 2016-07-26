#include "UIVolume.hpp"

UIVolume::UIVolume()
{
	myHovered = false;
	myClicked = false;
	myMouseX = 0;
	myVolume = 80;
}

void UIVolume::handleEvent(const sf::Event& event)
{
	UIControl::handleEvent(event);
	
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		myClicked = myHovered;
		if (myClicked)
			myVolume = myMouseX;
	}
	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
	{
		myClicked = false;
	}
	if (event.type == sf::Event::MouseMoved)
	{
		float x = event.mouseMove.x;
		float y = event.mouseMove.y;
		myHovered = (x >= myTruePosition.x && x <= myTruePosition.x + 80
				 && y >= myTruePosition.y - 80 && y <= myTruePosition.y);
		myMouseX = x;
		if (myMouseX > myTruePosition.x + 80)
			myMouseX = myTruePosition.x + 80;
		if (myMouseX < myTruePosition.x)
			myMouseX = myTruePosition.x;
		myMouseX -= myTruePosition.x;
		
		if (myClicked)
			myVolume = myMouseX;
	}
}

void UIVolume::draw(sf::RenderWindow * window)
{
	for (int i = 0; i < 80; i++)
	{
		int height = i / 2;
		sf::Color color = (myVolume >= i) ? (sf::Color(i * 2.5 + 25, 0, 0)) : (sf::Color(100, 30, 30));
		sf::RectangleShape line;
		line.setPosition(myTruePosition.x + i, myTruePosition.y - height);
		line.setSize(sf::Vector2f(1, height));
		line.setFillColor(color);
		window->draw(line);
	}
	if (myHovered || myClicked)
	{
		int volume100 = myVolume / 80.0f * 100;
		sf::Text volumeText(Globals::integerToString(volume100) + "%", Globals::Font, 12);
		volumeText.setPosition(myTruePosition.x, myTruePosition.y - 40);
		window->draw(volumeText);
		
		sf::RectangleShape line;
		line.setPosition(myTruePosition.x + myMouseX, myTruePosition.y - 45 + ((80 - myMouseX) / 2));
		line.setSize(sf::Vector2f(1, 10));
		line.setFillColor(sf::Color(230, 160, 160));
		window->draw(line);
		
		/*sf::Shape selectionLine = sf::Shape::Line(m_position.x + m_mouseX, m_position.y - 45 + ((80 - m_mouseX) / 2), m_position.x + m_mouseX, m_position.y - 35 + ((80 - m_mouseX) / 2), 2, sf::Color(200, 200, 200));
		window.Draw(selectionLine);*/
	}
}

bool UIVolume::isClicked()
{
	return myClicked;
}

float UIVolume::getVolume()
{
	return (float)myVolume / 80.0f;
}