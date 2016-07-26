#ifndef H_LSM_UICONTROL
#define H_LSM_UICONTROL

#include "Globals.hpp"

class UIControl : sf::NonCopyable
{
	private:
		void updatePosition();
		
	protected:
		UIAnchorType myAnchorType;
		sf::Vector2i myPosition;
		sf::Vector2i myTruePosition;
		bool myVisibility;
		
	public:
		UIControl();
		
		void setVisible(bool visible);
		bool isVisible();
		
		void setPosition(UIAnchorType anchorType, int x, int y);
		void setPosition(int x, int y);
		void setAnchorType(UIAnchorType anchorType);
		
		virtual void handleEvent(const sf::Event& event);
		virtual void update() {}
		virtual void draw(sf::RenderWindow * window) {}
};

#endif
