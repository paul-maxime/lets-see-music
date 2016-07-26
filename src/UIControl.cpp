#include "UIControl.hpp"
#include "MainWindow.hpp"

void UIControl::updatePosition()
{
	sf::Vector2i screenSize = Globals::Window->getSize();
	switch(myAnchorType)
	{
		case TOP_LEFT:
			myTruePosition.x = myPosition.x;
			myTruePosition.y = myPosition.y;
			break;
		case TOP_RIGHT:
			myTruePosition.x = screenSize.x - myPosition.x;
			myTruePosition.y = myPosition.y;
			break;
		case BOTTOM_LEFT:
			myTruePosition.x = myPosition.x;
			myTruePosition.y = screenSize.y - myPosition.y;
			break;
		case BOTTOM_RIGHT:
			myTruePosition.x = screenSize.x - myPosition.x;
			myTruePosition.y = screenSize.y - myPosition.y;
			break;
	}
}

UIControl::UIControl()
{
	myPosition.x = 0;
	myPosition.y = 0;
	myTruePosition.x = 0;
	myTruePosition.y = 0;
	myAnchorType = TOP_LEFT;
}

void UIControl::setVisible(bool visible)
{
	myVisibility = visible;
}

bool UIControl::isVisible()
{
	return myVisibility;
}

void UIControl::setPosition(UIAnchorType anchorType, int x, int y)
{
	myAnchorType = anchorType;
	myPosition.x = x;
	myPosition.y = y;
	updatePosition();
}

void UIControl::setPosition(int x, int y)
{
	myPosition.x = x;
	myPosition.y = y;
	updatePosition();
}

void UIControl::setAnchorType(UIAnchorType anchorType)
{
	myAnchorType = anchorType;
	updatePosition();
}

void UIControl::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::Resized)
		updatePosition();
}
