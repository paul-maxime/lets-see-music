#include "MainWindow.hpp"
#include "SoundManager.hpp"

MainWindow::MainWindow()
{
	myWindow = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "Let'see Music", sf::Style::Default, sf::ContextSettings(32));
	
	myWindow->setVerticalSyncEnabled(true);
	myWindow->setKeyRepeatEnabled(false);
	
	myView = new sf::View(sf::FloatRect(0, 0, 800, 600));
	myWindow->setView(*myView);
	
    glClearDepth(1.f);
    glClearColor(0.f, 0.f, 0.f, 0.f);
	
	myCurrentVisual = 0;
	myMenuOpened = false;
	myRepeating = false;
	myRecordType = 0;
	
	std::cout << "MainWindow initialized" << std::endl;
}

void MainWindow::initLogo()
{
	sf::Image logo;
	logo.loadFromFile(Globals::StartupPath + "img\\logo.png");
	myWindow->setIcon(logo.getSize().x, logo.getSize().y, logo.getPixelsPtr());
	std::cout << "Added logo.png to MainWindow" << std::endl;
}

void MainWindow::addControl(UIControl * control)
{
	myControls.push_back(control);
}

void MainWindow::addDisplay(DisplayMode * display)
{
	myDisplays.push_back(display);
}

void MainWindow::initControls()
{
	initLogo();
	
	myWindowPlaylist = new PlaylistWindow;
	myWindowPlaylist->setVisible(false);
	myWindowPlaylist->setPosition(TOP_LEFT, 50, 50);
	addControl(myWindowPlaylist);
	
	myButtonPlay = new UIButton("play");
	myButtonPlay->setPosition(BOTTOM_LEFT, 35, 40);
	addControl(myButtonPlay);
	
	myButtonPause = new UIButton("pause");
	myButtonPause->setPosition(BOTTOM_LEFT, 35, 40);
	myButtonPause->setVisible(false);
	addControl(myButtonPause);
	
	myButtonStop = new UIButton("stop");
	myButtonStop->setPosition(BOTTOM_LEFT, 85, 40);
	addControl(myButtonStop);
	
	myButtonArrow = new UIButton("arrow");
	myButtonArrow->setPosition(TOP_RIGHT, 26, 80);
	addControl(myButtonArrow);
	
	myButtonPlaylist = new UIButton("add");
	myButtonPlaylist->setPosition(TOP_RIGHT, 32, 125);
	myButtonPlaylist->setVisible(false);
	addControl(myButtonPlaylist);
	
	myButtonVisual = new UIButton("change");
	myButtonVisual->setPosition(TOP_RIGHT, 32, 175);
	myButtonVisual->setVisible(false);
	addControl(myButtonVisual);
	
	myButtonRecord = new UIButton("record");
	myButtonRecord->setPosition(TOP_RIGHT, 32, 225);
	myButtonRecord->setVisible(false);
	addControl(myButtonRecord);
	
	myLabelTitle = new UILabel;
	myLabelTitle->setText(Globals::Sound->getSoundTitle());
	myLabelTitle->setSize(16);
	myLabelTitle->setPosition(TOP_LEFT, 10, 10);
	addControl(myLabelTitle);
	
	myLabelFps = new UILabel;
	myLabelFps->setText("0 FPS");
	myLabelFps->setSize(16);
	myLabelFps->setPosition(TOP_RIGHT, 80, 10);
	addControl(myLabelFps);
	
	myLabelCurrentTime = new UILabel;
	myLabelCurrentTime->setText("0:00 / 0:00");
	myLabelCurrentTime->setSize(16);
	myLabelCurrentTime->setPosition(BOTTOM_LEFT, 125, 85);
	addControl(myLabelCurrentTime);
	
	myProgressBar = new UIProgressBar;
	myProgressBar->setPosition(BOTTOM_LEFT, 125, 57);
	addControl(myProgressBar);
	
	myVolume = new UIVolume;
	myVolume->setPosition(BOTTOM_RIGHT, 100, 22);
	addControl(myVolume);
	
	std::cout << "MainWindow : loaded " << myControls.size() << " controls" << std::endl;
	
	addDisplay(new DisplayWave);
	addDisplay(new DisplayHistogram);
	addDisplay(new DisplaySphere);
	addDisplay(new DisplayWater);
	addDisplay(new DisplayRecon);
	
	std::cout << "MainWindow : loaded " << myDisplays.size() << " displays" << std::endl;
}

MainWindow::~MainWindow()
{
	for (int i = 0; i < myControls.size(); i++)
		delete myControls[i];
	delete myView;
	std::cout << "MainWindow : Controls destroyed" << std::endl;
}

void MainWindow::startLoop()
{
	sf::Clock clock;
	sf::Clock updateClock;
    while (myWindow->isOpen())
	{
		updateClock.restart();
		update(clock.restart());
		display();
		sf::Time time = updateClock.restart();
		int sleepTime = 15 - time.asMilliseconds();
		if (sleepTime < 1) sleepTime = 1;
		sf::sleep(sf::milliseconds(sleepTime));
	}
}

void MainWindow::update(sf::Time elaspedTime)
{
	sf::Event event;
	while (myWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			myWindow->close();
		if (event.type == sf::Event::Resized)
		{
			glViewport(0, 0, event.size.width, event.size.height);
			delete myView;
			myView = new sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height));
			myWindow->setView(*myView);
			
			myLabelTitle->setSize(14 + (event.size.width / 300));
		}
		
		for (int i = 0; i < myControls.size(); i++)
			myControls[i]->handleEvent(event);
	}
	for (int i = 0; i < myControls.size(); i++)
		myControls[i]->update();
	
	if (Globals::Sound->isLoaded())
	{
		if (Globals::Sound->isPlaying() && !Globals::Sound->isCurrentlyPlaying())
		{
			Globals::Sound->stopSound();
			if (myRepeating)
				Globals::Sound->playSound();
		}
		if (myButtonPlay->onClick())
		{
			if (Globals::Sound->isPlaying())
				Globals::Sound->togglePause();
			else
				Globals::Sound->playSound();
		}
		if (myButtonPause->onClick())
		{
			Globals::Sound->togglePause();
		}
		if (myButtonStop->onClick())
		{
			Globals::Sound->stopSound();
		}
		if (myProgressBar->onClick())
		{
			if (!Globals::Sound->isPlaying())
				Globals::Sound->playSound();
			Globals::Sound->setPercentPosition(myProgressBar->getSelectedPercent());
		}
		if (myProgressBar->isClicked())
		{
			myLabelCurrentTime->setText(Globals::Sound->getPositionAsString(myProgressBar->getSelectedPercent()));
		}
	}
	
	if (myButtonVisual->onClick())
	{
		if (myButtonVisual->isRightClick())
			myCurrentVisual--;
		else
			myCurrentVisual++;
		
		if (myCurrentVisual < 0)
			myCurrentVisual = myDisplays.size() - 1;
		if (myCurrentVisual > myDisplays.size() - 1)
			myCurrentVisual = 0;
	}

	if (Globals::Sound->isPlaying())
	{
		bool soundPaused = Globals::Sound->isPaused();
		myButtonPlay->setVisible(soundPaused);
		myButtonPause->setVisible(!soundPaused);
		
		myLabelCurrentTime->setText(Globals::Sound->getPositionAsString());
		myProgressBar->setPercent(Globals::Sound->getPosition());
	}
	else
	{
		myButtonPlay->setVisible(true);
		myButtonPause->setVisible(false);
		myLabelCurrentTime->setText(Globals::Sound->getPositionAsString(0));
		myProgressBar->setPercent(0.0f);
	}
	
	if (myButtonArrow->onClick())
	{
		myMenuOpened = !myMenuOpened;
		myButtonArrow->flipHorizontally(myMenuOpened);
		myButtonVisual->setVisible(myMenuOpened);
		myButtonPlaylist->setVisible(myMenuOpened);
		myButtonRecord->setVisible(myMenuOpened);
	}
	
	if (myVolume->isClicked())
	{
		Globals::Sound->setVolume(myVolume->getVolume());
		Globals::Record->setVolume((myRecordType == 2 || myRecordType == 3) ? 0.0f : myVolume->getVolume());
	}
	
	if (myButtonRecord->onClick())
	{
		if (myRecordType == 2)
		{
			myRecordType = 0;
			myButtonRecord->setColor(sf::Color::White);
			Globals::Record->stopRecord();
			Globals::Record->setVolume(myVolume->getVolume());
		}
		else if (myRecordType == 0)
		{
			myRecordType = 1;
			myButtonRecord->setColor(sf::Color(120, 250, 120));
			Globals::Record->startRecord();
		}
		else if (myRecordType == 1)
		{
			myRecordType = 2;
			myButtonRecord->setColor(sf::Color(250, 120, 120));
			Globals::Record->setVolume(0.0f);
		}
	}
	
	if ((Globals::Sound->isPlaying() && !Globals::Sound->isPaused()) || Globals::Record->isRunning())
	{
		myDisplays[myCurrentVisual]->update();
	}
	
	myLabelFps->setText("FPS: " + Globals::integerToString(1 / elaspedTime.asSeconds()));
}

void MainWindow::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if (Globals::Sound->isPlaying() || Globals::Record->isRunning())
	{
		myDisplays[myCurrentVisual]->draw();
	}
	
	for (int i = 0; i < myControls.size(); i++)
		myControls[i]->draw(myWindow);
	
    myWindow->display();
}

sf::RenderWindow * MainWindow::getRenderWindow()
{
	return myWindow;
}

int MainWindow::getRecordType()
{
	return myRecordType;
}

sf::Vector2i MainWindow::getSize()
{
	sf::Vector2u size = myWindow->getSize();
	return sf::Vector2i(size.x, size.y);
}
