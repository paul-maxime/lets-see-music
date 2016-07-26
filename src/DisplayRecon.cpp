#include "DisplayRecon.hpp"
#include "MainWindow.hpp"
#include "SoundManager.hpp"

void sortLetters(std::vector<Letter>& letters)
{
    bool sorted = false;
    int length = letters.size();
	
    while(!sorted)
    {
        sorted = true;
        for(int i = 0; i < length-1; i++)
        {
            if(letters[i].power > letters[i+1].power)
            {
				Letter cpy = letters[i+1];
				letters[i+1] = letters[i];
				letters[i] = cpy;
                sorted = false;
            }
        }
        length--;
    }
}

void DisplayRecon::draw()
{
	SoundAnalyzer * analyzer = getAnalyzer();
	
	sf::RenderWindow * window = Globals::Window->getRenderWindow();
	sf::Text text("", Globals::Font, 128);
	bool found = false;
	
	text.setPosition(80, 80);
	
	if (analyzer->getPower() >= 1.0f)
	{
		Letter a;
		a.letter = "A";
		a.power = analyzer->getRegionForce(60, 120) / 60.0f;
		
		Letter e;
		e.letter = "E";
		e.power = analyzer->getRegionForce(100, 130) / 30.0f;
		
		Letter i;
		i.letter = "I";
		i.power = analyzer->getRegionForce(260, 300) / 40.0f;
		
		Letter o;
		o.letter = "O";
		o.power = analyzer->getRegionForce(20, 30) / 15.0f;
		
		Letter u;
		u.letter = "U";
		u.power = analyzer->getRegionForce(140, 180) / 80.0f;
		
		Letter et;
		et.letter = "Et";
		et.power = analyzer->getRegionForce(160, 340) / 180.0f;
		
		std::vector<Letter> letters;
		letters.push_back(a);
		letters.push_back(e);
		letters.push_back(i);
		letters.push_back(o);
		letters.push_back(u);
		letters.push_back(et);
		
		sortLetters(letters);
		
		found = true;
		text.setString(letters.at(4).letter);
	}
	
	if (found)
		window->draw(text);
	
	delete analyzer;
}
