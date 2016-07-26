#include "RecordManager.hpp"

RecordManager::RecordManager()
{
	myChannel = NULL;
	mySound = NULL;
	myRunning = false;
	myVolume = 1.0f;
	
	Globals::displayError(FMOD_System_Create(&mySystem));
	Globals::displayError(FMOD_System_SetSoftwareFormat(mySystem, SOUND_OUTPUTRATE, FMOD_SOUND_FORMAT_PCM16, 1, 1, FMOD_DSP_RESAMPLER_LINEAR));
	Globals::displayError(FMOD_System_Init(mySystem, 2, FMOD_INIT_NORMAL, NULL));
	
	std::cout << "RecordManager initialized" << std::endl;
}

RecordManager::~RecordManager()
{
	stopRecord();
	FMOD_System_Close(mySystem);
	FMOD_System_Release(mySystem);
	
	std::cout << "RecordManager destroyed" << std::endl;
}

void RecordManager::startRecord()
{
	if (myRunning) return;
	
    FMOD_CREATESOUNDEXINFO exinfo;
	
    memset(&exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
	
    exinfo.cbsize           = sizeof(FMOD_CREATESOUNDEXINFO);
    exinfo.numchannels      = 1;
    exinfo.format           = FMOD_SOUND_FORMAT_PCM16;
    exinfo.defaultfrequency = SOUND_OUTPUTRATE;
    exinfo.length           = exinfo.defaultfrequency * sizeof(short) * exinfo.numchannels / 10;
	
    Globals::displayError(FMOD_System_CreateSound(mySystem, 0, FMOD_2D | FMOD_SOFTWARE | FMOD_OPENUSER, &exinfo, &mySound));
	Globals::displayError(FMOD_Sound_SetMode(mySound, FMOD_LOOP_NORMAL));
	
	Globals::displayError(FMOD_System_RecordStart(mySystem, 0, mySound, true));
	Globals::displayError(FMOD_System_PlaySound(mySystem, (FMOD_CHANNELINDEX) 0, mySound, 0, &myChannel));
	
	myRunning = true;
	
	setVolume(myVolume);
}

void RecordManager::stopRecord()
{
	if (!myRunning) return;
	Globals::displayError(FMOD_Channel_Stop(myChannel));
	Globals::displayError(FMOD_System_RecordStop(mySystem, 0));
	Globals::displayError(FMOD_Sound_Release(mySound));
	myRunning = false;
}

bool RecordManager::isRunning()
{
	return myRunning;
}

void RecordManager::setVolume(float volume)
{
	myVolume = volume;
	if (!myRunning) return;
	Globals::displayError(FMOD_Channel_SetVolume(myChannel, volume));
}

float * RecordManager::getWaveData(int size)
{
	if (!myRunning) return NULL;
	
	float * waveArray = new float[size];
	Globals::displayError(FMOD_Channel_GetWaveData(myChannel, waveArray, size, 0));
	return waveArray;
}

float * RecordManager::getSpectrumData(int size)
{
	if (!myRunning) return NULL;
	
	float * spectrum = new float[size];
	Globals::displayError(FMOD_Channel_GetSpectrum(myChannel, spectrum, size, 0, FMOD_DSP_FFT_WINDOW_RECT));
	return spectrum;
}

SoundAnalyzer * RecordManager::getAnalyzer()
{
	if (!myRunning) return NULL;
	
	float * spectrum = getSpectrumData(8192);
	SoundAnalyzer * analyzer = new SoundAnalyzer(spectrum);
	delete spectrum;
	return analyzer;
}
