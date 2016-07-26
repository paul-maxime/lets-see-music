#ifndef H_LSM_UIVOLUME
#define H_LSM_UIVOLUME

#include "Globals.hpp"
#include "UIControl.hpp"

class UIVolume : public UIControl
{
	private:
		bool myHovered;
		bool myClicked;
		int myMouseX;
		int myVolume;
		
	public:
		UIVolume();
		
		virtual void handleEvent(const sf::Event& event);
		virtual void draw(sf::RenderWindow * window);
		
		bool isClicked();
		float getVolume();
};

#endif
