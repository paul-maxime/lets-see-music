#include "Globals.hpp"
#include "MainWindow.hpp"
#include "SoundManager.hpp"
#include "RecordManager.hpp"

std::string getCurrentDirectory(char * arg)
{
	int pos = Strings::LastIndexOf(arg, '\\');
	char * cDirectory = Strings::Substring(arg, 0, pos+1);
	std::string currentDirectory(cDirectory);
	delete cDirectory;
	return currentDirectory;
}

int main(int argc, char **argv)
{
	Globals::StartupPath = getCurrentDirectory(argv[0]);
	std::cout << "Startup path : " << Globals::StartupPath << std::endl;
	
	Globals::Font.loadFromFile(Globals::StartupPath + "font\\x360.ttf");
	std::cout << "Font initialized" << std::endl;
	
	Globals::Sound = new SoundManager;
	Globals::Record = new RecordManager;
	
	if (argc >= 2)
	{
		Globals::Sound->loadSound(argv[1]);
		Globals::Sound->playSound();
	}
	
	Globals::Window = new MainWindow;
	Globals::Window->initControls();
	Globals::Window->startLoop();
	delete Globals::Window;
	delete Globals::Sound;
	
	std::cout << "return 0" << std::endl;
    return 0;
}
