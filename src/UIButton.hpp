#ifndef H_LSM_UIBUTTON
#define H_LSM_UIBUTTON

#include "Globals.hpp"
#include "UIControl.hpp"

class UIButton : public UIControl
{
	private:
		sf::Texture myTexture;
		sf::Sprite mySprite;
		
		bool myHovered;
		bool myClicked;
		bool myWasClicked;
		bool myRightClick;
		
	public:
		UIButton(const char * buttonName);
		
		virtual void handleEvent(const sf::Event& event);
		virtual void draw(sf::RenderWindow * window);
		
		void flipHorizontally(bool flip);
		void setColor(sf::Color color);
		
		bool onClick();
		bool isRightClick();
};

#endif
