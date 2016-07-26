#include "DisplaySphere.hpp"
#include "MainWindow.hpp"
#include "SoundManager.hpp"

DisplaySphere::DisplaySphere()
{
	myRotation = 0.0f;
}

void DisplaySphere::update()
{
	SoundAnalyzer * analyzer = getAnalyzer();

	myRotation += analyzer->getPower() / 3.0f;
	if (myRotation >= 360.0f)
		myRotation -= 360.0f;
	
	delete analyzer;
}

void DisplaySphere::draw()
{
	OpenGLUtils::Enable3d();
	
	gluLookAt(2.6, 1, 1.81, 2.12, 1.0, 0, 0, 1, 0);
	
	SoundAnalyzer * analyzer = getAnalyzer();
	SoundSpike * spikes = analyzer->getSpikes();
	delete analyzer;
		
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			int id = j * 12 + i;
			int size = log(1+spikes[id].value) * 500.0f;
			int colorValue = size * 1.5;
			if (size > 0 && size < 400)
			{
				sf::Color color;
				if (colorValue > 255)
					colorValue = 255;
				
				color = sf::Color(colorValue, 255 - colorValue, 0);
				
				if (size > 25)
					size = 25;
				
				OpenGLUtils::DrawSphere((float) (i * 80 + 100) / 300.0f, (float) (j * 60 + 100) / 300.0f, 0.0f, (size / 220.0f), myRotation, 15, color);
			}
		}
	}
	
	OpenGLUtils::Enable2d();
}
