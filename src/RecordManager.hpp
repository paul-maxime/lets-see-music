#ifndef H_LSM_RECORDMANAGER
#define H_LSM_RECORDMANAGER

#include "Globals.hpp"
#include "SoundAnalyzer.hpp"

class RecordManager
{
	private:
		FMOD_SYSTEM * mySystem;
		FMOD_SOUND * mySound;
		FMOD_CHANNEL * myChannel;
		bool myRunning;
		float myVolume;
		
	public:
		RecordManager();
		~RecordManager();
		
		void startRecord();
		void stopRecord();
		
		bool isRunning();
		
		void setVolume(float volume);
		
		float * getWaveData(int size);
		float * getSpectrumData(int size);
		
		SoundAnalyzer * getAnalyzer();
};

#endif
