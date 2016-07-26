#ifndef H_LSM_DISPLAYMODE
#define H_LSM_DISPLAYMODE

#include "Globals.hpp"
#include "OpenGLUtils.hpp"
#include "SoundManager.hpp"
#include "RecordManager.hpp"

class DisplayMode : sf::NonCopyable
{
	protected:
		float * getWaveData(int size);
		float * getSpectrumData(int size);
		SoundAnalyzer * getAnalyzer();
		
	public:
		virtual void update() {}
		virtual void draw() {}
};

#endif