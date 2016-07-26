#ifndef H_LSM_DISPLAYRECON
#define H_LSM_DISPLAYRECON

#include "Globals.hpp"
#include "DisplayMode.hpp"

struct Letter
{
	std::string letter;
	float power;
};

class DisplayRecon : public DisplayMode
{
	public:
		void draw();
};

#endif
