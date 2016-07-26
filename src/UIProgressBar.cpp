#include "UIProgressBar.hpp"
#include "MainWindow.hpp"

UIProgressBar::UIProgressBar()
{
	myPercent = 0.0f;
	myHovered = false;
	myClicked = false;
	myWasClicked = false;
}

void UIProgressBar::handleEvent(const sf::Event& event)
{
	UIControl::handleEvent(event);
	
	if (event.type == sf::Event::MouseMoved)
	{
		float x = event.mouseMove.x;
		float y = event.mouseMove.y;
		sf::Vector2i windowSize = Globals::Window->getSize();
		
		float maxX = windowSize.x - 110.0f;
		float maxY = myTruePosition.y + 35.0f;
		
		myHovered = (x >= myTruePosition.x && x <= maxX
				 && y >= myTruePosition.y && y <= maxY);
				 
		myMousePosition.x = x;
		if (myMousePosition.x > maxX)
			myMousePosition.x = maxX;
		if (myMousePosition.x < myTruePosition.x)
			myMousePosition.x = myTruePosition.x;
	}
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		myClicked = myHovered;
	}
	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
	{
		myWasClicked = myClicked;
		myClicked = false;
	}
}

void UIProgressBar::draw(sf::RenderWindow * window)
{
	sf::Vector2i windowSize = Globals::Window->getSize();
	
	sf::RectangleShape rectangle;
	rectangle.setPosition(sf::Vector2f(myTruePosition.x, myTruePosition.y));
	rectangle.setSize(sf::Vector2f(windowSize.x - myTruePosition.x - 110.0f, 35.0f));
	rectangle.setFillColor(sf::Color(120, 30, 30));
	rectangle.setOutlineThickness(2);
	rectangle.setOutlineColor(sf::Color(60, 10, 10));
	
	window->draw(rectangle);
	
	float drawedPercent = myPercent;
	if (myClicked)
		drawedPercent = getSelectedPercent();
	
	if (drawedPercent > 0.0f)
	{
		sf::RectangleShape innerRectangle;
		innerRectangle.setPosition(sf::Vector2f(myTruePosition.x, myTruePosition.y));
		innerRectangle.setSize(sf::Vector2f((float)(rectangle.getSize().x) * drawedPercent, rectangle.getSize().y));
		innerRectangle.setFillColor(sf::Color(160, 60, 60));
		
		window->draw(innerRectangle);
	}
	
	if (myHovered)
	{
		sf::RectangleShape line;
		line.setPosition(myMousePosition.x, myTruePosition.y - 5);
		line.setSize(sf::Vector2f(1, 10));
		line.setFillColor(sf::Color(230, 160, 160));
		window->draw(line);
		line.setPosition(myMousePosition.x, myTruePosition.y + 30);
		window->draw(line);
	}
}

void UIProgressBar::setPercent(float percent)
{
	myPercent = percent;
	if (2 < 0.0f) myPercent = 0.0f;
	if (myPercent > 1.0f) myPercent = 1.0f;
}

bool UIProgressBar::isClicked()
{
	return myClicked;
}

bool UIProgressBar::onClick()
{
	if (myWasClicked)
	{
		myWasClicked = false;
		return true;
	}
	return false;
}

float UIProgressBar::getSelectedPercent()
{
	sf::Vector2i windowSize = Globals::Window->getSize();
	
	float location = myMousePosition.x - myTruePosition.x;
	float size = windowSize.x - 110.0f - myTruePosition.x;
	return (location / size);
}

