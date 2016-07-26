#include "DisplayWater.hpp"
#include "MainWindow.hpp"

DisplayWater::DisplayWater()
{
	depth = 3;
	i = 0;
	t = 0;
	f = 1;
	
	int i, j;
	for (i = 0; i < WATERSIZE; i++)
	for(j = 0; j < WATERSIZE; j++) {
		water[0][j][i] = 0;
		water[1][j][i] = 0;
	}
}

void DisplayWater::update()
{
	int x, y;
	float n;
	
	for (y = 1; y < WATERSIZE-1; y++) {
		for (x = 1; x < WATERSIZE-1; x++) {
			n = ( water[t][x-1][y] +
			water[t][x+1][y] +
			water[t][x][y-1] +
			water[t][x][y+1]
			) /2;
			n -= water [f][x][y];
			n = n - (n / DAMP);
			water[f][x][y] = n;
		}
	}

	y = 0;
	for (x = 1; x < WATERSIZE-1; x++) {
		n = ( water[t][x-1][y] +
		water[t][x+1][y] +
		water[t][x][y+1]
		) /2;
		n -= water[f][x][y];
		n = n - (n / DAMP);
		water[f][x][y] = n;
	}

	x = 0;
	for (y = 1; y < WATERSIZE-1; y++) {
		n = ( water[t][x+1][y] +
		water[t][x][y-1] +
		water[t][x][y+1]
		) /2;
		n -= water[f][x][y];
		n = n - (n / DAMP);
		water[f][x][y] = n;
	}

	y = WATERSIZE-1;
	for (x = 1; x < WATERSIZE-1; x++) {
		n = ( water[t][x-1][y] +
		water[t][x+1][y] +
		water[t][x][y-1]
		) /2;
		n -= water[f][x][y];
		n = n - (n / DAMP);
		water[f][x][y] = n;
	}
	
	SoundAnalyzer * analyzer = getAnalyzer();
	
	water[f][100][65] += analyzer->getRegionForce(1, 100) * 200;
	
	water[f][45][100] += analyzer->getRegionForce(100, 200) * 100;
	water[f][165][100] += analyzer->getRegionForce(300, 400) * 100;
	
	water[f][80][165] += analyzer->getRegionForce(400, 700) * 300;
	water[f][120][165] += analyzer->getRegionForce(700, 1000) * 300;
}

void DisplayWater::draw()
{
	int i, j, tmp;
	
	sf::Vector2i windowSize = Globals::Window->getSize();
	w = windowSize.x;
	h = windowSize.y;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (GLfloat) w/ (GLfloat) h, 1.0, 2000.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	
	glPushMatrix();
	glTranslatef(0, 0, spin_z-220);
	glRotatef(spin_x, 0, 1, 0);
	glRotatef(spin_y-60, 1, 0, 0);

	glBegin(GL_POINTS);
	for(i = 0; i < WATERSIZE; i++) {
		for(j = 0; j < WATERSIZE; j++) {
			if (abs(water[t][j][i]) < 50)
			{
				glColor3f(0,0,255);
				glVertex3f(j-WATERSIZE/2, i-WATERSIZE/2, water[t][j][i]);
			}
		}
	}
	glEnd();
	
	tmp = t; t = f; f = tmp;

	glPopMatrix();
	
	OpenGLUtils::Enable2d();
}
