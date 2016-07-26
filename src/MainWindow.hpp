#ifndef H_LSM_MAINWINDOW
#define H_LSM_MAINWINDOW

#include "Globals.hpp"
#include "PlaylistWindow.hpp"
#include "UIControl.hpp"
#include "UIButton.hpp"
#include "UILabel.hpp"
#include "UIProgressBar.hpp"
#include "UIVolume.hpp"
#include "DisplayWave.hpp"
#include "DisplayHistogram.hpp"
#include "DisplaySphere.hpp"
#include "DisplayWater.hpp"
#include "DisplayRecon.hpp"

class MainWindow : sf::NonCopyable
{
	private:
		sf::RenderWindow * myWindow;
		sf::View * myView;
		std::vector<UIControl *> myControls;
		std::vector<DisplayMode *> myDisplays;
		
		void initLogo();
		void addControl(UIControl * control);
		void addDisplay(DisplayMode * display);
		
		int myCurrentVisual;
		bool myMenuOpened;
		bool myRepeating;
		int myRecordType;
		
		PlaylistWindow * myWindowPlaylist;
		
		UIButton * myButtonPlay;
		UIButton * myButtonPause;
		UIButton * myButtonStop;
		UIButton * myButtonVisual;
		UIButton * myButtonArrow;
		UIButton * myButtonPlaylist;
		UIButton * myButtonRecord;
		UILabel * myLabelTitle;
		UILabel * myLabelFps;
		UILabel * myLabelCurrentTime;
		UIProgressBar * myProgressBar;
		UIVolume * myVolume;
	
	public:
		MainWindow();
		~MainWindow();
		
		sf::RenderWindow * getRenderWindow();
		
		void initControls();
		
		void startLoop();
		void update(sf::Time time);
		void display();
		
		int getRecordType();
		
		sf::Vector2i getSize();
};

#endif
