#include "SoundManager.hpp"

SoundManager::SoundManager()
{
	Globals::displayError(FMOD_System_Create(&mySystem));
	Globals::displayError(FMOD_System_SetSoftwareFormat(mySystem, SOUND_OUTPUTRATE, FMOD_SOUND_FORMAT_PCM16, 2, 0, FMOD_DSP_RESAMPLER_LINEAR));
	Globals::displayError(FMOD_System_Init(mySystem, 2, FMOD_INIT_NORMAL, NULL));
	mySound = NULL;
	myChannel = NULL;
	mySoundTitle = "";
	myPlaying = false;
	myVolume = 1.0f;
	
	std::cout << "SoundManager initialized" << std::endl;
}

SoundManager::~SoundManager()
{
	closeSound();
	Globals::displayError(FMOD_System_Close(mySystem));
	Globals::displayError(FMOD_System_Release(mySystem));
}

bool SoundManager::initTags()
{
	std::cout << "SoundManager : Loading sound tags" << std::endl;
	
	FMOD_TAG tag;
	if (FMOD_Sound_GetTag(mySound, "TITLE", 0, &tag) == FMOD_OK)
	{
		mySoundTitle = std::string((char*)tag.data);
		std::cout << "    TITLE: " << (char*)tag.data << std::endl;
		if (FMOD_Sound_GetTag(mySound, "ARTIST", 0, &tag) == FMOD_OK)
		{
			mySoundTitle += " - " + std::string((char*)tag.data);
			std::cout << "    ARTIST: " << (char*)tag.data << std::endl;
		}
		return true;
	}
	return false;
}

void SoundManager::loadSound(const char * filename)
{
	if (mySound != NULL)
		closeSound();
	
	std::cout << "SoundManager : Loading sound " << filename << std::endl;
	Globals::displayError(FMOD_System_CreateSound(mySystem, filename, FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &mySound));
	
	if (!initTags())
		mySoundTitle = filename;
	
	std::cout << "SoundManager : Sound loaded" << std::endl;
}

void SoundManager::closeSound()
{
	if (mySound == NULL) return;
	if (myPlaying)
		stopSound();
	Globals::displayError(FMOD_Sound_Release(mySound));
	mySound = NULL;
	mySoundTitle = "";
	std::cout << "SoundManager : Sound destroyed" << std::endl;
}

void SoundManager::playSound()
{
	if (mySound == NULL || myPlaying) return;
	Globals::displayError(FMOD_System_PlaySound(mySystem, (FMOD_CHANNELINDEX) 0, mySound, 0, &myChannel));
	myPlaying = true;
	setVolume(myVolume);
}

void SoundManager::togglePause()
{
	if (!myPlaying) return;
	Globals::displayError(FMOD_Channel_SetPaused(myChannel, !isPaused()));
}

void SoundManager::stopSound()
{
	if (!myPlaying) return;
	Globals::displayError(FMOD_Channel_Stop(myChannel));
	myChannel = NULL;
	myPlaying = false;
}

bool SoundManager::isLoaded()
{
	return mySound != NULL;
}

bool SoundManager::isPaused()
{
	FMOD_BOOL paused;
	FMOD_Channel_GetPaused(myChannel, &paused);
	return paused ? true : false;
}

bool SoundManager::isPlaying()
{
	if (!isLoaded()) return false;
	return myPlaying;
}

bool SoundManager::isCurrentlyPlaying()
{
	if (!myPlaying) return false;
	
	FMOD_BOOL playing;
	FMOD_Channel_IsPlaying(myChannel, &playing);
	return playing ? true : false;
}

std::string SoundManager::getSoundTitle()
{
	return mySoundTitle;
}

void SoundManager::setPercentPosition(float position)
{
	if (!myPlaying) return;
	
	unsigned int lenms;
	FMOD_Sound_GetLength(mySound, &lenms, FMOD_TIMEUNIT_MS);
	
	int newPosition = lenms * position;
	if (newPosition > lenms) newPosition = lenms;
	FMOD_Channel_SetPosition(myChannel, newPosition, FMOD_TIMEUNIT_MS);
}

float SoundManager::getPosition()
{
	if (!myPlaying) return 0.0f;
	
	unsigned int ms;
	unsigned int lenms;
	
	FMOD_Channel_GetPosition(myChannel, &ms, FMOD_TIMEUNIT_MS);
	FMOD_Sound_GetLength(mySound, &lenms, FMOD_TIMEUNIT_MS);
	
	return (float)ms / (float)lenms;
}

std::string SoundManager::getPositionAsString()
{
	unsigned int ms;
	unsigned int lenms;
	
	FMOD_Channel_GetPosition(myChannel, &ms, FMOD_TIMEUNIT_MS);
	FMOD_Sound_GetLength(mySound, &lenms, FMOD_TIMEUNIT_MS);
	
	return Globals::timeToString(ms, lenms);
}

void SoundManager::setVolume(float volume)
{
	myVolume = volume;
	if (!myPlaying) return;
	Globals::displayError(FMOD_Channel_SetVolume(myChannel, volume));
}

std::string SoundManager::getPositionAsString(float percent)
{
	unsigned int ms;
	unsigned int lenms;
	
	FMOD_Sound_GetLength(mySound, &lenms, FMOD_TIMEUNIT_MS);
	ms = lenms * percent;
	
	return Globals::timeToString(ms, lenms);
}

float * SoundManager::getWaveData(int size)
{
	if (!myPlaying) return NULL;
	
	float * waveArray = new float[size];
	Globals::displayError(FMOD_Channel_GetWaveData(myChannel, waveArray, size, 0));
	return waveArray;
}

float * SoundManager::getSpectrumData(int size)
{
	if (!myPlaying) return NULL;
	
	float * spectrum = new float[size];
	Globals::displayError(FMOD_Channel_GetSpectrum(myChannel, spectrum, size, 0, FMOD_DSP_FFT_WINDOW_RECT));
	return spectrum;
}

SoundAnalyzer * SoundManager::getAnalyzer()
{
	if (!myPlaying) return NULL;
	
	float * spectrum = getSpectrumData(8192);
	SoundAnalyzer * analyzer = new SoundAnalyzer(spectrum);
	delete spectrum;
	return analyzer;
}
