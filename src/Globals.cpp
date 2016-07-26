#include "Globals.hpp"

namespace Globals
{
	std::string StartupPath;
	MainWindow * Window = NULL;
	SoundManager * Sound = NULL;
	RecordManager * Record = NULL;
	sf::Font Font;
	
	void displayError(FMOD_RESULT result)
	{
		if (result == FMOD_OK) return;
		std::cout << "fmod error : " << FMOD_ErrorString(result) << std::endl;
	}
	
	std::string	integerToString(int value)
	{
		std::ostringstream oss;
		oss << value;
		return oss.str();
	}
	
	std::string timeToString(unsigned int ms, unsigned int lenms)
	{
		std::string position;
		
		int totalSeconds = ms / 1000;
		int seconds = totalSeconds % 60;
		int minutes = totalSeconds / 60;
		
		position = integerToString(minutes) + ":";
		if (seconds < 10) position += "0";
		position += integerToString(seconds);
		
		position += " / ";
		
		totalSeconds = lenms / 1000;
		seconds = totalSeconds % 60;
		minutes = totalSeconds / 60;
		
		position += integerToString(minutes) + ":";
		if (seconds < 10) position += "0";
		position += integerToString(seconds);
		
		return position;
	}
	
	bool getDirectory(std::string dir, std::vector<std::string> & files)
	{
		DIR *dp;
		struct dirent *dirp;
		if((dp  = opendir(dir.c_str())) == NULL) {
			return false;
		}

		while ((dirp = readdir(dp)) != NULL) {
			std::string file(dirp->d_name);
			if (file.length() > 3)
				files.push_back(std::string(dirp->d_name));
		}
		closedir(dp);
		return true;
	}
}
