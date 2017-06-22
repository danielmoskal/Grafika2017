#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<map>
#include<glut.h>
#include<string>
#include<vector>
#include"glm.hpp"
#include"Dron.h"
#include"Camera.h"
#include"ObjLoader.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include"glm.h"
#include "AntTweakBar.h"

typedef struct {
	int width;
	int height;
	char* title;

	float field_of_view_angle;
	float z_near;
	float z_far;
} glutWindow;

OBJLoader l;
glutWindow win;

bool collision = false;
float odleglosc = 0;
float odlegloscD = odleglosc;


extern int fillMenu, colorMenu, mainMenu;

//Move entity
extern float cx, cy, cz;
extern float pochL, pochR, pochF, pochB;

// angle of rotation for the camera direction
extern float horizontalAngle;

//actual vector representing he camera's direction
extern float lx, lz;
// XZ position of the camera
extern float x, z, y;

//These variables will be zero when no key is being presses
extern float deltaAngle, deltaMove, deltaMoveDown;
extern int xOrigin;

using namespace std;

// width and height of the window
extern int h, w;

void drawDron()
{
	Dron dron;
}

void kolizja()
{
	odleglosc = 0;
	float PrzeszkodaX[20] = { 21 };
	float PrzeszkodaZ[20] = { -57.9 };
	for (int i = 0; i < 1; i++)
	{
		odleglosc = sqrt((x - PrzeszkodaX[i])*(x - PrzeszkodaX[i]) + (z - PrzeszkodaZ[i])*(z - PrzeszkodaZ[i]));
		if (odleglosc < 2.7)
		{
			collision = true;
			break;
		}
		else
		{
			collision = false;
		}

	}

}

void renderBitmapString(float x, float y, float z, void *font, char *string)
{
	char *c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void renderStrokeFontString(float x, float y, float z, void *font, char *string)
{
	char *c;
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(0.002f, 0.002f, 0.002f);
	for (c = string; *c != '\0'; c++) {
		glutStrokeCharacter(font, *c);
	}
	glPopMatrix();
}

void setProjection(int w1, int h1)
{
	float ratio;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	ratio = 1.0f * w1 / h1;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w1, h1);

	// Set the clipping volume
	gluPerspective(45, ratio, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
}

//==================================================
//					Wczytywanie obiektow
//==================================================
//koment
GLMmodel *tras;
void Trasa()
{
	if (!tras)
	{
		tras = glmReadOBJ("trasa.obj");
		if (!tras)
			exit(0);
		glmFacetNormals(tras);
		glmVertexNormals(tras, 90.0);
	}
	glmDraw(tras, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Cylinder");
	glmDraw(tras, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Cylinder.001");
	glmDraw(tras, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Plane");
	glmDraw(tras, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Sphere");
	glmDraw(tras, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Sphere.001");
	glmDraw(tras, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Sphere.002");
	glPushMatrix();
	glPopMatrix();
}


void drawObject1()
{
	vector<Vector3> vertices = l.GetVertices();
	vector<Vector3> normals = l.GetNormals();
	vector<Vector2> textureCoords = l.GetTextureCoords();
	vector<FaceData> faces = l.GetFaces();

	glPushMatrix();
	glTranslatef(0, 3, cz); //cx cy cz


	glColor3f(1.0f, 1.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	{
		for (int i = 0; i < faces.size(); i++)
		{
			/*	glTexCoord2f(faces[i].Textures.X, faces[i].Textures.Y);
			glNormal3f(faces[i].Normals.X, faces[i].Normals.Y, faces[i].Normals.Z);
			glVertex3f(faces[i].Vertices.X, faces[i].Vertices.Y, faces[i].Vertices.Z);*/
			glBegin(GL_TRIANGLES);

			glTexCoord2f(textureCoords[faces[i].Textures.X - 1].X, textureCoords[faces[i].Textures.X - 1].Y);
			//glNormal3f(normals[faces[i].Normals.X-1].X, normals[faces[i].Normals.X-1].Y, normals[faces[i].Normals.X-1].Z);
			glVertex3f(vertices[faces[i].Vertices.X - 1].X, vertices[faces[i].Vertices.X - 1].Y, vertices[faces[i].Vertices.X - 1].Z);

			glTexCoord2f(textureCoords[faces[i].Textures.Y - 1].X, textureCoords[faces[i].Textures.Y - 1].Y);
			//glNormal3f(normals[faces[i].Normals.Y-1].X, normals[faces[i].Normals.Y-1].Y, normals[faces[i].Normals.Y-1].Z);
			glVertex3f(vertices[faces[i].Vertices.Y - 1].X, vertices[faces[i].Vertices.Y - 1].Y, vertices[faces[i].Vertices.Y - 1].Z);

			glTexCoord2f(textureCoords[faces[i].Textures.Z - 1].X, textureCoords[faces[i].Textures.Z - 1].Y);
			//glNormal3f(normals[faces[i].Normals.Z-1].X, normals[faces[i].Normals.Z-1].Y, normals[faces[i].Normals.Z-1].Z);
			glVertex3f(vertices[faces[i].Vertices.Z - 1].X, vertices[faces[i].Vertices.Z - 1].Y, vertices[faces[i].Vertices.Z - 1].Z);

			glEnd();
		}
	}
	glPopMatrix();
}

void lights()
{
	GLfloat lightColor0[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat lightPos0[] = { 5.0f, 5.0f, 12.0f, 1.0f };
	//GLfloat lightPos0[] = {5.0f, 5.0f, 12.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(lightPos0[0], lightPos0[1], lightPos0[2]);
	glutWireSphere(2.0, 100, 100);
	glPopMatrix();

}


//==================================================
//					     END
//==================================================

void DrawString(int x, int y, int z, char * string)
{
	// po³o¿enie napisu
	glRasterPos3i(x, y,z);

	// wyœwietlenie napisu
	int len = strlen(string);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]);

}

void drawSnowMan()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	{
		glScalef(1, 1, 1);
		glColor3f(1.0f, 1.0f, 1.0f);

		//Draw Body
		glTranslatef(0.0f, 0.75f, 0.0f);
		glutSolidSphere(0.75f, 20, 20);

		// Draw Head
		glTranslatef(0.0f, 1.0f, 0.0f);
		glutSolidSphere(0.25f, 20, 20);

		// Draw Eyes
		glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(0.05f, 0.10f, 0.18f);
		glutSolidSphere(0.05f, 10, 10);
		glTranslatef(-0.1f, 0.0f, 0.0f);
		glutSolidSphere(0.05f, 10, 10);
		glPopMatrix();

		// Draw Nose
		glColor3f(1, 1, 1);
		glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
		glutSolidCone(0.08f, 0.5f, 10, 2);

		glColor3f(1.0f, 1.0f, 1.0f);
	}

}


void display()
{
	if (deltaMove)
		computePos(deltaMove);
	if (deltaMoveDown)
		computePos(deltaMoveDown);
	if (deltaAngle)
		computeDir(deltaAngle);
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Trasa();
	lights();
	kolizja();
	if (collision)
	{
		deltaMove = 0;
	}
	odlegloscD = odleglosc - 2.6;
	char str[10];
	sprintf(str, "%f", odlegloscD);
	DrawString(5, 3, -58, "PRZESZKODA --> ");
	DrawString(13, 2,-58, str);
	glPushMatrix();
	glTranslatef(25, -1, 25);
	glScalef(3, 3, 3);
	drawSnowMan();
	glPopMatrix();


	// Reset transformations
	glLoadIdentity();

	glPushMatrix();
	glRotatef(pochL + pochR, 0, 0, 1);
	glRotatef(pochF + pochB, 0, 1, 0);
	glRotatef(-180, 0, 1, 0);
	glTranslatef(-0.2, 0, 1);
	glScalef(0.01, 0.01, 0.01);
	drawDron();
	glPopMatrix();

	//Set the camera
	gluLookAt(x, y, z,
		x + lx, y, z + lz,
		0.0f, 1.0f, 0.0f);

	//==============================================================
	TwDraw();
	glFlush();				//skierowanie polecen do wykonania
	glutSwapBuffers();		//zamiana buforow koloru
	glutPostRedisplay();		//zeby aktywowac dzialanie
}

void changeSize(int ww, int hh)
{
	h = hh;
	w = ww;
	//Prevent divide by zero, when window is too short
	if (h == 0)
		h = 1;
	float ratio = 1.0* w / h;

	//Use the projection Matrix
	glMatrixMode(GL_PROJECTION);

	//Reset Matrix
	glLoadIdentity();

	//Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	//Set the correct perspective
	gluPerspective(45.0f, ratio, 0.1f, 1000.0f);

	//Get back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}


//==================================================
//					MAIN
//==================================================

void init()
{
	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, win.width, win.height);
	GLfloat aspect = (GLfloat)win.width / win.height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(win.field_of_view_angle, aspect, win.z_near, win.z_far);
	glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_SMOOTH);
	glClearColor(1.0f, 1.0f, 1.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	GLfloat amb_light[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat diffuse[] = { 0.6, 0.6, 0.6, 1 };
	GLfloat specular[] = { 0.7, 0.7, 0.3, 1 };

	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	TwInit(TW_OPENGL, NULL);
	TwWindowSize(win.width, win.height);
	TwBar *myBar;
	myBar = TwNewBar("System");
	//TwAddVarRW(myBar, "kat Y: ", TW_TYPE_FLOAT, &systembat.speed, "label='Predkosc: ' ");
	TwAddVarRW(myBar, "X: ", TW_TYPE_FLOAT, &x, "group=Pozycja label='x: ' ");
	TwAddVarRW(myBar, "y: ", TW_TYPE_FLOAT, &y, "group=Pozycja label='y: ' ");
	TwAddVarRW(myBar, "z: ", TW_TYPE_FLOAT, &z, "group=Pozycja label='z: ' ");
	TwAddVarRW(myBar, "od: ", TW_TYPE_FLOAT, &odlegloscD, "group=Przeszkoda label='odleglosc: ' ");
	//TwAddVarRW(myBar, "kat X: ", TW_TYPE_FLOAT, &systembat.katX, "group=Katy label='kat X: ' ");
	//TwAddVarRW(myBar, "Nachylenie: ", TW_TYPE_FLOAT, &dron.nachyl, "group=Katy label='Nachylenie: ' ");
}



int main(int argc, char **argv)
{
	// set window values
	win.width = 640;
	win.height = 480;
	win.title = "Projekt Grafika";
	win.field_of_view_angle = 45;
	win.z_near = 1.0f;
	win.z_far = 500.0f;

	// initialize and run program
	glutInit(&argc, argv);                                      // GLUT initialization
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);  // Display Mode
	glutInitWindowSize(win.width, win.height);                  // set window size
	glutCreateWindow(win.title);                                // create Window
	glutDisplayFunc(display);                                   // register Display Function
	glutIdleFunc(display);                                  // register Idle Function

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	init();

	glutMainLoop();
	TwTerminate();
	return 0;
}