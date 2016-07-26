#include "PlaylistWindow.hpp"

PlaylistWindow::PlaylistWindow()
{
	if (!Globals::getDirectory(Globals::StartupPath + "\\music\\", myFiles))
		std::cout << "PlaylistWindow : Can't read music directory" << std::endl;
}

void PlaylistWindow::handleEvent(const sf::Event& event)
{
	UIControl::handleEvent(event);
	
	if (!myVisibility) return;
}

void PlaylistWindow::draw(sf::RenderWindow * window)
{
	if (!myVisibility) return;
	
	
}