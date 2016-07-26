#ifndef H_LSM_UIPROGRESSBAR
#define H_LSM_UIPROGRESSBAR

#include "Globals.hpp"
#include "UIControl.hpp"

class UIProgressBar : public UIControl
{
	private:
		float myPercent;
		bool myHovered;
		bool myClicked;
		bool myWasClicked;
		sf::Vector2i myMousePosition;
		
	public:
		UIProgressBar();
		
		virtual void handleEvent(const sf::Event& event);
		virtual void draw(sf::RenderWindow * window);
		
		void setPercent(float percent);
		void setPercent(int value, int maxValue);
		
		bool isClicked();
		bool onClick();
		float getSelectedPercent();
};

#endif
