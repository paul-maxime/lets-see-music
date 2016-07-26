#ifndef H_LSM_DISPLAYWATER
#define H_LSM_DISPLAYWATER

#include "Globals.hpp"
#include "DisplayMode.hpp"

#define WATERSIZE 200
#define DAMP 20

class DisplayWater : public DisplayMode
{
	private:
		float water[2] [WATERSIZE] [WATERSIZE];
		int spin_x, spin_y, spin_z;
		int h, w;
		int old_x, old_y, move_z;
		int depth;
		int i;
		int t, f;

	public:
		DisplayWater();
		virtual void update();
		virtual void draw();
};

#endif
