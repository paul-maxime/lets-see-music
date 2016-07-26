#ifndef H_LSM_GLOBALS
#define H_LSM_GLOBALS

#define SFML_STATIC

#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <dirent.h>
#include <cstring>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include <fmodex/fmod.h>
#include <fmodex/fmod_errors.h>

#include "Strings.hpp"

#define SOUND_OUTPUTRATE 48000

enum UIAnchorType
{
	TOP_LEFT,
	TOP_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_RIGHT
};

class MainWindow;
class SoundManager;
class RecordManager;

namespace Globals
{
	extern std::string StartupPath;
	extern MainWindow * Window;
	extern SoundManager * Sound;
	extern RecordManager * Record;
	extern sf::Font Font;
	
	void displayError(FMOD_RESULT result);
	std::string integerToString(int value);
	std::string timeToString(unsigned int ms, unsigned int lenms);
	bool getDirectory(std::string dir, std::vector<std::string> & files);
}

#endif
