#define _CRT_SECURE_NO_WARNINGS
#include "Camera.h"


float cx = 0, cy = 0, cz = 0;
float pochL = 0.0f, pochR = 0.0f, pochF = 0.0f, pochB = 0.0f;

//actual vector representing he camera's direction
float lx = 0.0f, lz = -1.0f;
// XZ position of the camera
float x = 0.0f, z = 5.0f, y = 1.0f;

//These variables will be zero when no key is being presses
float horizontalAngle = 3.14f, verticalAngle = 0.0f;

float deltaAngle = 0.0f;
char gameModeString[40] = "1366x768";
float mouseSpeed = 0.000008f;

glm::vec3 position = glm::vec3(0, 0, 5);

float speed = 3.0f; // 3 units / second
//=========================================================================

float deltaMove = 0;
float deltaMoveDown = 0;
int xOrigin = -1, yOrigin = 1, h, w;

void init();

extern bool collision;

void processNormalKeys(unsigned char key, int x, int y)
{
	if (key == 'w') { cz -= 0.5; } if (key == 's') { cz += 0.5; }	//forward, back
	if (key == 'a') { cx -= 0.5; } if (key == 'd') { cx += 0.5; }	//left, right
	if (key == 'q') { cy += 0.5; } if (key == 'z') { cy -= 0.5; }
	if (key == 'x') { horizontalAngle += 0.66; } if (key == 'c') { horizontalAngle -= 0.66; }
	if (key == 27) { exit(0); }
}

//klawisze specjalne
void pressKey(int key, int x, int y)
{
	int mod;
	float fraction = 0.1f;
	switch (key)
	{
	case GLUT_KEY_LEFT:
		deltaAngle += -0.006f;
		while (pochL < 15)
		{
			pochL += 0.000001f;
		}
		break;
	case GLUT_KEY_RIGHT:
		deltaAngle += 0.006f;
		while (pochR > -15)
		{
			pochR -= 0.000001f;
		}
		break;
	case GLUT_KEY_UP:
		deltaMove += 0.5f;
		break;
	case GLUT_KEY_DOWN:
		deltaMoveDown += -1.0f;

		break;
	}
}

void releaseKey(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT: deltaAngle = 0; pochL = 0; break;
	case GLUT_KEY_RIGHT: deltaAngle = 0.0f; pochR = 0; break;
	case GLUT_KEY_UP: deltaMove = 0; pochF = 0; break;
	case GLUT_KEY_DOWN: deltaMove = 0.0f; pochB = 0; deltaMoveDown = 0.0f; break;
	}
}

void mouseButton(int button, int state, int x, int y)
{
	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON)
	{
		//glutSetCursor(GLUT_CURSOR_NONE);	//zeby nie przeszkadzal w wdioku
		// when the button is released
		if (state == GLUT_UP)
		{
			horizontalAngle += deltaAngle;
			horizontalAngle += mouseSpeed * deltaAngle * float(xOrigin / 2 - x);
			xOrigin = -1;
		}
		else
		{ //(state = GLUT_DOWN)
			xOrigin = x;
		}
	}
	else if (button == GLUT_RIGHT_BUTTON)	//zeby sie pojawil ponownie
	{
		glutSetCursor(1);
	}
}

void mouseMove(int x, int y)
{	// this will only be true when the left button is down
	if (xOrigin >= 0)
	{
		// update deltaAngle
		deltaAngle = (x - xOrigin) * mouseSpeed;

		// update camera's direction

		lx = cos(verticalAngle) * sin(horizontalAngle);
		lz = sin(verticalAngle);
	}
}

void computePos(float deltaMove)
{
	float s = 0.1f;
	//poz += przemieszczenie * kat * szybkosc
	x += deltaMove * lx * s;
	z += deltaMove * lz * s;
}

void computeDir(float deltaAngle)
{
	horizontalAngle += deltaAngle;
	lx = sin(horizontalAngle);
	lz = -cos(horizontalAngle);

}