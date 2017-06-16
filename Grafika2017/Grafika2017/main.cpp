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
#include"Area.h"
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


//do menu
#define RED 1
#define GREEN 2
#define BLUE 3
#define ORANGE 4
#define WHITE 5

#define LINE 1
#define FILL 2
///////////////

OBJLoader l;


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
extern float deltaAngle, deltaMove;
extern int xOrigin;

extern float red, green, blue;

using namespace std;
int cn;  //quad number

		 //scale of snowman
float scale = 1.0f;

//menu status
extern int menuFlag;

//default font
void *font = GLUT_BITMAP_HELVETICA_12;

#define INT_GLUT_BITMAP_8_BY_13 1
#define INT_GLUT_BITMAP_9_BY_15 2
#define INT_GLUT_BITMAP_TIMES_ROMAN_10  3
#define INT_GLUT_BITMAP_TIMES_ROMAN_24  4
#define INT_GLUT_BITMAP_HELVETICA_10  5
#define INT_GLUT_BITMAP_HELVETICA_12  6
#define INT_GLUT_BITMAP_HELVETICA_18  7

// variables to compute frames per second
int frame;
long time, timebase;
char s[50];
extern char currentMode[80];

// width and height of the window
extern int h, w;

// this string keeps the last good setting
// for the game mode
extern char gameModeString[40];
extern int current_window;


struct Quads
{
	int x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;
	float r, g, b;
	int state;
	int total;
}; Quads Q[100];

void addQuad()
{
	Q[0].state++; if (Q[0].state > 4) { Q[0].state = 1; }
	int st = Q[0].state;

	if (st == 1) { Q[0].total++; cn = Q[0].total; }
	if (st == 1) { Q[cn].x1 = cx; Q[cn].y1 = cy; Q[cn].z1 = cz; }
	if (st == 1 || st == 2) { Q[cn].x2 = cx; Q[cn].y2 = cy; Q[cn].z2 = cz; }
	if (st == 1 || st == 2 || st == 3) { Q[cn].x3 = cx; Q[cn].y3 = cy; Q[cn].z3 = cz; }
	if (st == 1 || st == 2 || st == 3 || st == 4) { Q[cn].x4 = cx; Q[cn].y4 = cy; Q[cn].z4 = cz; }
}

void drawDron()
{

	//glPushMatrix();
	/*glRotatef(pochL + pochR, 0, 0, 1);
	glTranslatef(-3, 0, -25);
	glRotatef(horizontalAngle, 0, 1, 0);
	glScalef(0.12, 0.12, 0.12);*/
	Dron dron;
	//glPopMatrix();
}

void drawQuads()
{
	int i;
	for (i = 1; i < Q[0].total + 1; i++)
	{
		glBegin(GL_QUADS);
		glColor3f(Q[i].r, Q[i].g, Q[i].b);
		glVertex3f(Q[i].x1, Q[i].y1, Q[i].z1);
		glVertex3f(Q[i].x2, Q[i].y2, Q[i].z2);
		glVertex3f(Q[i].x3, Q[i].y3, Q[i].z3);
		glVertex3f(Q[i].x4, Q[i].y4, Q[i].z4);
		glEnd();
	}

}


void theCube()
{
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(cx, cy, cz);
	glutSolidCube(0.4);
	glPopMatrix();
}


void drawGrid()
{
	int i;
	for (i = 0; i < 40; i++)
	{
		glPushMatrix();
		if (i < 20) { glTranslatef(0, 0, i); }
		if (i >= 20) { glTranslatef(i - 20, 0, 0); glRotatef(-90, 0, 1, 0); }

		glBegin(GL_LINES);
		glColor3f(1, 1, 1); glLineWidth(1);
		glVertex3f(0, -5, 0);	glVertex3f(19, -5, 0);
		glEnd();
		glPopMatrix();
	}
}

void wall()
{
	const float height = 5.0;
	const float width = 6.0;

	glBegin(GL_QUADS);

	glNormal3f(0.0, 0.0, -1.0);                                  // -1.0 jest kluczowe
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-width / 2.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(width / 2.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(width / 2.0, height, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-width / 2.0, height, 0.0);

	glNormal3f(0.0, 0.0, 1.0);                                // a tu 1.0
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-width / 2.0, 0.0, 0.01);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(width / 2.0, 0.0, 0.01);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(width / 2.0, height, 0.01);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-width / 2.0, height, 0.01);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void drawSnowMan()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	{
		glScalef(scale, scale, scale);
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
		glColor3f(red, green, blue);
		glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
		glutSolidCone(0.08f, 0.5f, 10, 2);

		glColor3f(1.0f, 1.0f, 1.0f);
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

void setOrthographicProjection() {

	// switch to projection mode
	glMatrixMode(GL_PROJECTION);

	// save previous matrix which contains the
	//settings for the perspective projection
	glPushMatrix();

	// reset matrix
	glLoadIdentity();

	// set a 2D orthographic projection
	gluOrtho2D(0, w, h, 0);

	// switch back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void restorePerspectiveProjection() {

	glMatrixMode(GL_PROJECTION);
	// restore previous projection matrix
	glPopMatrix();

	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
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
	//glmDraw(tras, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Plane");
	glmDraw(tras, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Cone");
	glmDraw(tras, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Cone.001");
	glmDraw(tras, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Plane");
	glmDraw(tras, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Cone.002");
	glmDraw(tras, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Cone.003");
	glmDraw(tras, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Cone.004");
	glmDraw(tras, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Cone.005");
	glmDraw(tras, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Cone.006");
	glmDraw(tras, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Cone.007");
	glmDraw(tras, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Cone.008");
	glmDraw(tras, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Cone.009");
	glmDraw(tras, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Cone.010");
	glmDraw(tras, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Cone.011");
	glmDraw(tras, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Cone.012");
	glmDraw(tras, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Cone.013");
	glmDraw(tras, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Cone.014");
	glmDraw(tras, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Cone.015");
	glmDraw(tras, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Cone.016");
	glmDraw(tras, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Cone.017");
	glmDraw(tras, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Cone.018");
	glmDraw(tras, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Cone.019");

	glPushMatrix();
	glPopMatrix();
}


void drawObject1()
{
	vector<Vector3> vertices = l.GetVertices();
	vector<Vector3> normals = l.GetNormals();
	vector<Vector2> textureCoords = l.GetTextureCoords();
	vector<FaceData> faces = l.GetFaces();


	//glPushMatrix();
	//glTranslatef(cx, cy, cz);
	//glRotatef(-90, 0, 1, 0);
	//glRotatef(horizontalAngle, 0, 1, 0);



	glPushMatrix();
	glTranslatef(0, 3, cz); //cx cy cz
							//glRotatef(-90, 0, 1, 0);
							//glRotatef(horizontalAngle, 0, 1, 0);

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


void drawGround()
{
	glColor3f(0.0f, 0.9f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();
}


void drawArea()
{
	glPushMatrix();
	glTranslatef(0, 2, 0);
	glScalef(0.2, 0.2, 0.2);
	Area area;
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



void display()
{
	if (deltaMove)
		computePos(deltaMove);
	if (deltaAngle)
		computeDir(deltaAngle);

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	//glTranslatef(-13, 0, -45);
	//drawGrid();
	//drawQuads();
	//drawArea();

	//glScalef(1 , 1, 1);
	//drawObject1();

	//drawGround();
	//drawObject1();
	//wall();
	Trasa();

	lights();

	// Draw 36 SnowMen
	for (int i = -3; i < 3; i++)
		for (int j = -3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i*10.0, 0, j * 10.0);
			drawSnowMan();
			glPopMatrix();
		}

	// Reset transformations
	glLoadIdentity();

	glPushMatrix();
	glRotatef(pochL + pochR, 0, 0, 1);
	glRotatef(pochF + pochB, 0, 1, 0);
	glTranslatef(-3, 0, -25);
	glScalef(0.2, 0.2, 0.2);
	drawDron();
	glPopMatrix();


	//komentarz do sprawdzenia gita

	//Set the camera
	gluLookAt(x, y, z,
		x + lx, y, z + lz,
		0.0f, 1.0f, 0.0f);






	//==============================================================
	// Code to compute frames per second
	frame++;

	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf_s(s, "FPS:%4.2f",
			frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}

	// Code to display a string (fps) with bitmap fonts
	setOrthographicProjection();

	glPushMatrix();
	glLoadIdentity();
	//renderBitmapString(5, 30, 0, GLUT_BITMAP_HELVETICA_18, s);
	renderBitmapString(5, 15, 0, font, s);
	renderBitmapString(5, 30, 0, font, (char *)"F1 - Game Mode  640x480 32 bits");
	renderBitmapString(5, 45, 0, font, (char *)"F2 - Game Mode  800x600 32 bits");
	renderBitmapString(5, 60, 0, font, (char *)"F3 - Game Mode 1024x768 32 bits");
	renderBitmapString(5, 75, 0, font, (char *)"F4 - Window Mode");
	renderBitmapString(5, 90, 0, font, (char *)"Esc - Quit");
	renderBitmapString(5, 105, 0, font, currentMode);
	glPopMatrix();

	restorePerspectiveProjection();

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
//					MENUS
//==================================================

void processMenuStatus(int status, int x, int y) {

	if (status == GLUT_MENU_IN_USE)
		menuFlag = 1;
	else
		menuFlag = 0;
}

void processMainMenu(int option) {

	// nothing to do in here
	// all actions are for submenus
}

void processFillMenu(int option) {

	switch (option) {

	case FILL: glPolygonMode(GL_FRONT, GL_FILL); break;
	case LINE: glPolygonMode(GL_FRONT, GL_LINE); break;
	}
}

void processColorMenu(int option) {

	switch (option) {
	case RED:
		red = 1.0f;
		green = 0.0f;
		blue = 0.0f; break;
	case GREEN:
		red = 0.0f;
		green = 1.0f;
		blue = 0.0f; break;
	case BLUE:
		red = 0.0f;
		green = 0.0f;
		blue = 1.0f; break;
	case ORANGE:
		red = 1.0f;
		green = 0.5f;
		blue = 0.5f; break;
	}
}

void createPopupMenus()
{
	fillMenu = glutCreateMenu(processFillMenu);

	glutAddMenuEntry("Fill", FILL);
	glutAddMenuEntry("Line", LINE);

	colorMenu = glutCreateMenu(processColorMenu);
	glutAddMenuEntry("Red", RED);
	glutAddMenuEntry("Blue", BLUE);
	glutAddMenuEntry("Green", GREEN);
	glutAddMenuEntry("Orange", ORANGE);

	mainMenu = glutCreateMenu(processMainMenu);

	glutAddSubMenu("Polygon Mode", fillMenu);
	glutAddSubMenu("Color", colorMenu);
	// attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// this will allow us to know if the menu is active
	glutMenuStatusFunc(processMenuStatus);
}

//==================================================
//					MAIN
//==================================================

void init()
{
	l.LoadFromFile("cube.obj");

	gluPerspective(35, 1.0f, 0.1f, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST | GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1.0f);
	glClearColor(0.0, 0.0, 1.0, 1);

	glutDisplayFunc(display);
	glutReshapeFunc(changeSize);
	glutIdleFunc(display);

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	//model loading


}



int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Projekt grafika");
	current_window = glutGetWindow();

	init();

	createPopupMenus();


	glutMainLoop();

	return 1;
}