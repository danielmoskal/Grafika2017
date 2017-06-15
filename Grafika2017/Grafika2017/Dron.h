#pragma once
#include<glut.h>

class Dron
{
public:
	Dron();
	~Dron();

	void walecOtwarty(GLfloat x, GLfloat y, GLfloat z, GLfloat srednicaXZ, GLfloat wysokoscY, int red, int green, int blue);
	void walecZamkniety(GLfloat x, GLfloat y, GLfloat z, GLfloat srednicaXZ, GLfloat wysokoscY, int red, int green, int blue);
	void kolo(GLfloat x, GLfloat y, GLfloat z, GLfloat srednicaXZ, int red, int green, int blue);
	void okrag(GLfloat x, GLfloat y, GLfloat z, GLfloat srednicaXZ, GLfloat gruboscLini, int red, int green, int blue);
	void stozek(GLfloat srodekPodstawyX, GLfloat srodekPodstawyY, GLfloat srodekPodstawyZ, GLfloat srednicaXZ, GLfloat wysokoscY, int red, int green, int blue);
	void romb(GLfloat x, GLfloat y, GLfloat z, GLfloat dlugosc, GLfloat szerokosc, GLfloat wysokosc, float red, float green, float blue);
	void ostroslup(GLfloat x, GLfloat y, GLfloat z, GLfloat szerokosc, GLfloat wysokosc, float red, float green, float blue);
	void wiatrak(GLfloat x, GLfloat y, GLfloat z, GLfloat promienLopatki);
	void lacznikSmigloBaza(GLfloat smigloX, GLfloat smigloY, GLfloat smigloZ);
	void kamera(GLfloat x, GLfloat y, GLfloat z);
	void pierscien(GLfloat x, GLfloat y, GLfloat z, GLdouble r, GLdouble h);
	void krzyz(GLfloat x, GLfloat y, GLfloat z, GLfloat r);
};

