#include "SoundAnalyzer.hpp"

SoundAnalyzer::SoundAnalyzer(float * spectrum)
{
	mySpectrum = spectrum;
	myPower = 0.0f;
	
	mySpikes = new SoundSpike[132];
	for (int i = 0; i < 132; i++)
		mySpikes[i].frequency = -1.0f;
	
	for (int i = 3; i < 5461; i++)
	{
		float hz = (float)i * (float)SOUND_OUTPUTRATE / 8192.0f;
		int noteid = frequencyToNote(hz);
		if (mySpikes[noteid].frequency == -1.0f || spectrum[i] > mySpikes[noteid].value)
		{
			mySpikes[noteid].frequency = hz;
			mySpikes[noteid].value = spectrum[i];
		}
		myPower += spectrum[i];
	}
}

int SoundAnalyzer::frequencyToNote(float hz)
{
	float currentdistance = 48000.0f;
	int besti = 0;
	for (int i = 0; i < 132; i++)
	{
		float distance = fabs(noteFrequency[i] - hz);
		
		if (distance < currentdistance)
		{
			currentdistance = distance;
			besti = i;
		}
	}
	return besti;
}

float SoundAnalyzer::getPower()
{
	return myPower;
}

float SoundAnalyzer::getRegionForce(int min, int max)
{
	min *= 4;
	max *= 4;
	float total = 0.0f;
	for (int i = min; i < max; i++)
		total += mySpectrum[i];
	return total;
}

SoundSpike * SoundAnalyzer::getSpikes()
{
	return mySpikes;
}
