#include "DisplayHistogram.hpp"
#include "MainWindow.hpp"
#include "SoundManager.hpp"

void DisplayHistogram::draw()
{
	sf::Vector2i windowSize = Globals::Window->getSize();
	
	int size = 2;
	while (size < windowSize.x)
		size *= 2;
	
	float * spectrum = getSpectrumData(size);
	
	OpenGLUtils::Enable2d();
	
	float length = (windowSize.y - 200.0f);
	
	for (int i = 0 ; i < windowSize.x; i++)
	{
		float valueY = log10(1+spectrum[i]) * 15.0f;
		if (valueY > 1.0f) valueY = 1.0f;
		if (valueY < 0.0f) valueY = 0.0f;
		float maxY = length * valueY;
		
		OpenGLUtils::DrawLine(i, length + 100 - maxY, i, length + 100, sf::Color(140, 25, 25));
	}
	
	delete spectrum;
}
