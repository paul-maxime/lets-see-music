#ifndef H_LSM_SOUNDMANAGER
#define H_LSM_SOUNDMANAGER

#include "Globals.hpp"
#include "SoundAnalyzer.hpp"

class SoundManager
{
	private:
		FMOD_SYSTEM * mySystem;
		FMOD_SOUND * mySound;
		FMOD_CHANNEL * myChannel;
		
		std::string mySoundTitle;
		bool myPlaying;
		float myVolume;
		
		bool initTags();
		
	public:
		SoundManager();
		~SoundManager();
		
		void loadSound(const char * filename);
		void closeSound();
		
		void playSound();
		void togglePause();
		void stopSound();
		
		bool isLoaded();
		bool isPaused();
		bool isPlaying();
		bool isCurrentlyPlaying();
		
		std::string getSoundTitle();
		
		void setPercentPosition(float position);
		float getPosition();
		std::string getPositionAsString();
		std::string getPositionAsString(float percent);
		
		void setVolume(float volume);
		
		float * getWaveData(int size);
		float * getSpectrumData(int size);
		
		SoundAnalyzer * getAnalyzer();
};

#endif
