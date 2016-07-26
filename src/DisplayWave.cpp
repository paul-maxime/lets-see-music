#include "DisplayWave.hpp"
#include "MainWindow.hpp"
#include "SoundManager.hpp"

void DisplayWave::draw()
{
	sf::Vector2i windowSize = Globals::Window->getSize();
	float * wave = getWaveData(windowSize.x);
	
	OpenGLUtils::Enable2d();
	float y, lastY;
	for (int i = 0; i < windowSize.x - 2; i += 2)
	{
		y = (windowSize.y / 2) + (windowSize.y / 3) * wave[i];
		if (i != 0)
			OpenGLUtils::DrawLine(i - 2, lastY, i, y, sf::Color(140, 25, 25));
		lastY = y;
	}
	
	delete wave;
}