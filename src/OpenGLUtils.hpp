#ifndef H_LSM_OPENGLUTILS
#define H_LSM_OPENGLUTILS

#include "Globals.hpp"
#include <cmath>

namespace OpenGLUtils
{
	void 		Enable3d				();
	void 		Enable2d				();
	
	void 		DrawLine				(int x, int y, int x2, int y2, sf::Color color);
	void 		DrawRectangle			(int x, int y, int x2, int y2, sf::Color color);
	void 		DrawCircle				(float x, float y, float r, sf::Color color);
	
	void		DrawSphere				(float x, float y, float z, float radius, float angle, int stacks, sf::Color color);
	void		DrawPointWIP			(float x, float y, float z);
}

#endif
