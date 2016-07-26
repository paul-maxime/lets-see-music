#ifndef H_LSM_DISPLAYSPHERE
#define H_LSM_DISPLAYSPHERE

#include "Globals.hpp"
#include "DisplayMode.hpp"

class DisplaySphere : public DisplayMode
{
	private:
		float myRotation;

	public:
		DisplaySphere();
		virtual void update();
		virtual void draw();
};

#endif
