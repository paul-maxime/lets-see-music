#ifndef H_LSM_UILABEL
#define H_LSM_UILABEL

#include "Globals.hpp"
#include "UIControl.hpp"

class UILabel : public UIControl
{
	private:
		sf::String myText;
		int mySize;
		
	public:
		UILabel();
	
		void setText(sf::String text);
		void setText(std::string text);
		void setText(const char * text);
		void setText(char * text);
		
		void setSize(int size);
		
		virtual void draw(sf::RenderWindow * window);
};

#endif
