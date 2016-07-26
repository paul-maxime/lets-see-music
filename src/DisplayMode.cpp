#include "DisplayMode.hpp"
#include "MainWindow.hpp"

float * DisplayMode::getWaveData(int size)
{
	int type = Globals::Window->getRecordType();
	if (type == 1 || type == 2)
		return Globals::Record->getWaveData(size);
	return Globals::Sound->getWaveData(size);
}

float * DisplayMode::getSpectrumData(int size)
{
	int type = Globals::Window->getRecordType();
	if (type == 1 || type == 2)
		return Globals::Record->getSpectrumData(size);
	return Globals::Sound->getSpectrumData(size);
}

SoundAnalyzer * DisplayMode::getAnalyzer()
{
	int type = Globals::Window->getRecordType();
	if (type == 1 || type == 2)
		return Globals::Record->getAnalyzer();
	return Globals::Sound->getAnalyzer();
}
