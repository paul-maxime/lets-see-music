#ifndef H_LSM_PLAYLISTWINDOW
#define H_LSM_PLAYLISTWINDOW

#include "Globals.hpp"
#include "UIControl.hpp"

class PlaylistWindow : public UIControl
{
	private:
		std::vector<std::string> myFiles;
		
	public:
		PlaylistWindow();
		
		virtual void handleEvent(const sf::Event& event);
		virtual void draw(sf::RenderWindow * window);
		
};

#endif
