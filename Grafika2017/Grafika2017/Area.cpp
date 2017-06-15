#include "Area.h"
#include<math.h>
#define GL_PI 3.14

Area::Area()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	{
		drzewo(40, -20, 55);
		drzewo(-54, -20, 20);
		drzewo(120, -20, -45);
		drzewo(-140, -20, -78);
		podstawa();
	}
}


Area::~Area()
{
}

void Area::podstawa()
{
	glBegin(GL_TRIANGLE_FAN);
	glColor3ub(50, 190, 20);
	glVertex3f(0, -20, 0);
	for (float k = 0; k < 2 * GL_PI + GL_PI / 24; k += GL_PI / 24)
	{
		glVertex3f(sin(k) * 200, -20, cos(k) * 200);
	}
	glEnd();
}

void Area::drzewo(GLfloat x, GLfloat y, GLfloat z)
{
	glBegin(GL_TRIANGLE_FAN);
	glColor3ub(0, 255, 100);
	glVertex3f(x, y + 7, z);
	for (float k = 0 - GL_PI / 9; k <= GL_PI + GL_PI / 6 + GL_PI / 24; k += GL_PI / 24)
	{
		glVertex3f(x + cos(k) * 10, y + 12 + sin(k) * 10, z);
	}
	glEnd();

	glColor3ub(60, 25, 0);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < 16; i++)
	{
		glVertex3f(x + -1.5, y + i, z + 0);
		glVertex3f(x + 1.5, y + i, z + 0);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3ub(0, 255, 100);
	glVertex3f(z, y + 7, x);
	for (float k = 0 - GL_PI / 9; k <= GL_PI + GL_PI / 6 + GL_PI / 24; k += GL_PI / 24)
	{
		glVertex3f(z, y + 12 + sin(k) * 10, x + cos(k) * 10);
	}
	glEnd();

	glColor3ub(60, 25, 0);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < 16; i++)
	{
		glVertex3f(z, y + i, x + -1.5);
		glVertex3f(z, y + i, x + 1.5);
	}
	glEnd();
}
