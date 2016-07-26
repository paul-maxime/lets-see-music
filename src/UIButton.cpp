#include "UIButton.hpp"

UIButton::UIButton(const char * buttonName)
{
	myVisibility = true;
	
	myHovered = false;
	myClicked = false;
	myWasClicked = false;
	myRightClick = false;
	
	myTexture.loadFromFile(Globals::StartupPath + "img\\buttons\\" + buttonName + ".png");
	myTexture.setSmooth(true);
	mySprite.setTexture(myTexture);
	mySprite.setOrigin(myTexture.getSize().x / 2, myTexture.getSize().y / 2);
	std::cout << "Loaded UIButton " << buttonName << ".png" << std::endl;
}

void UIButton::handleEvent(const sf::Event& event)
{
	UIControl::handleEvent(event);
	
	if (myVisibility == false)
		return;
	
	if (event.type == sf::Event::MouseButtonPressed)
	{
		float x = event.mouseButton.x;
		float y = event.mouseButton.y;
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			myClicked = myHovered;
			myRightClick = false;
		}
		else if (event.mouseButton.button == sf::Mouse::Right)
		{
			myClicked = myHovered;
			myRightClick = true;
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased)
	{
		float x = event.mouseButton.x;
		float y = event.mouseButton.y;
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (myClicked && !myRightClick)
			{
				myClicked = false;
				myWasClicked = myHovered;
			}
		}
		else if (event.mouseButton.button == sf::Mouse::Right)
		{
			if (myClicked && myRightClick)
			{
				myClicked = false;
				myWasClicked = myHovered;
			}
		}
	}
	else if (event.type == sf::Event::MouseMoved)
	{
		float x = event.mouseMove.x;
		float y = event.mouseMove.y;
		float sizeX = myTexture.getSize().x / 2;
		float sizeY = myTexture.getSize().y / 2;
		myHovered = (x >= myTruePosition.x - sizeX && x <= myTruePosition.x + sizeX
						&& y >= myTruePosition.y - sizeY && y <= myTruePosition.y + sizeY);
	}
}

void UIButton::draw(sf::RenderWindow * window)
{
	if (!myVisibility) return;
	
	mySprite.setPosition(myTruePosition.x, myTruePosition.y);
	if (myHovered && myClicked)
		mySprite.setScale(1.1f, 1.1f);
	else if (myHovered)
		mySprite.setScale(1.2f, 1.2f);
	else
		mySprite.setScale(1.0f, 1.0f);
	
	window->draw(mySprite);
}

void UIButton::flipHorizontally(bool flip)
{
	mySprite.setRotation(flip ? 180.0f : 0.0f);
}

void UIButton::setColor(sf::Color color)
{
	mySprite.setColor(color);
}

bool UIButton::onClick()
{
	if (myWasClicked)
	{
		myWasClicked = false;
		return true;
	}
	return false;
}

bool UIButton::isRightClick()
{
	return myRightClick;
}