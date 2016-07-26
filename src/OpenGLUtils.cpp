#include "OpenGLUtils.hpp"
#include "MainWindow.hpp"

#define FLOAT_PI 3.141592653589793f

namespace OpenGLUtils
{
	void Enable3d()
	{
		sf::Vector2i windowSize = Globals::Window->getSize();
	
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(70.f, (float)windowSize.x / (float)windowSize.y, 1.f, 1000.f);
		glEnable(GL_DEPTH_TEST);
	}

	void Enable2d()
	{
		sf::Vector2i windowSize = Globals::Window->getSize();
	
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, windowSize.x, windowSize.y, 0, 0, 1);
		glMatrixMode(GL_MODELVIEW);
		glDisable(GL_DEPTH_TEST);
	}
	
	void DrawLine(int x, int y, int x2, int y2, sf::Color color)
	{
		glColor3ub(color.r, color.g, color.b);
		glBegin(GL_LINES);
		glVertex2i(x, y);
		glVertex2i(x2, y2);
		glEnd();
	}
	

	void DrawRectangle(int x, int y, int x2, int y2, sf::Color color)
	{
		glColor3ub(color.r, color.g, color.b);
		glBegin(GL_QUADS);
		glVertex2i(x, y);
		glVertex2i(x2, y);
		glVertex2i(x2, y2);
		glVertex2i(x, y2);
		glEnd();
	}
	
	void DrawCircle(float x, float y, float r, sf::Color color)
	{
		int segments = (int) (r * FLOAT_PI);
		glColor3ub(color.r, color.g, color.b);
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y);
		for (int n = 0; n <= segments; ++n )
		{
			float const t = 2 * FLOAT_PI * (float)n/(float)segments;
			glVertex2f(x + sin(t)*r, y + cos(t)*r);
		}
		glEnd();
	}
	
	void DrawSphere(float x, float y, float z, float radius, float angle, int stacks, sf::Color color)
	{
		GLUquadric* quad = gluNewQuadric();
		gluQuadricDrawStyle(quad, GLU_LINE);
	
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(x, y, z);
		glRotatef(angle, 1.5f, 1.0f, 1.1f);
		
		glColor3ub(color.r, color.g, color.b);
		gluSphere(quad, radius, stacks, stacks);
		
		gluDeleteQuadric(quad);
	}
	
	void DrawPoint(float x, float y, float z)
	{
		glBegin(GL_POINTS);
			glVertex3f(x, y, z);
		glEnd();
	}
}
