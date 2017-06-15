#include "Dron.h"
#include<math.h>
#define GL_PI 3.14

Dron::Dron()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	{
		

		kamera(-20, 0, -27);	// obiekt dokladnie pomiedzy czterema wiatrakami
		wiatrak(0, 0, 0, 15);
		wiatrak(40, 0, 40, 15);
		wiatrak(0, 0, 40, 15);
		wiatrak(40, 0, 0, 15);
		pierscien(20, -4, 20, 15, 2.5);
		krzyz(20, -2.75, 20, 1.25);
		walecZamkniety(20, -4, 20, 1.25, -5, 100, 100, 100);	//uchwyt do kamery
		lacznikSmigloBaza(0, 0, 0);  //lacznik wirnika o podanych wspolrzednych itd.
		lacznikSmigloBaza(40, 0, 0);
		lacznikSmigloBaza(40, 0, 40);
		lacznikSmigloBaza(0, 0, 40);
		romb(20, -8, 18, 2.5, -5, -5, 0.0, 0.3, 0.3);	//detale w kamerce
		romb(20, -8, 18, 2.5, 5, -5, 0.0, 0.3, 0.3);
		ostroslup(-2, 0, -2, 3, -4, 0.5, 0.0, 0.0);		//detale pod wiatrakami
		ostroslup(39, 0, 39, 3, -4, 0.5, 0.0, 0.0);
		ostroslup(-2, 0, 39, 3, -4, 0.5, 0.0, 0.0);
		ostroslup(39, 0, -2, 3, -4, 0.5, 0.0, 0.0);
	}
	
}


Dron::~Dron()
{
}

void Dron::walecOtwarty(GLfloat x, GLfloat y, GLfloat z, GLfloat srednicaXZ, GLfloat wysokoscY, int red, int green, int blue)
{
	glColor3ub(red, green, blue);
	glBegin(GL_TRIANGLE_STRIP);
	for (float k = 0; k < 2 * GL_PI + GL_PI / 12; k += GL_PI / 24)
	{
		glVertex3d(x + sin(k) * srednicaXZ, y + wysokoscY, z + cos(k) * srednicaXZ);
		glVertex3d(x + sin(k) * srednicaXZ, y, z + cos(k) * srednicaXZ);
	}
	glEnd();
}

void Dron::walecZamkniety(GLfloat x, GLfloat y, GLfloat z, GLfloat srednicaXZ, GLfloat wysokoscY, int red, int green, int blue)
{
	glColor3ub(red, green, blue);
	glBegin(GL_TRIANGLE_STRIP);
	for (float k = 0; k < 2 * GL_PI + GL_PI / 12; k += GL_PI / 24)
	{
		glVertex3d(x + sin(k) * srednicaXZ, y + wysokoscY, z + cos(k) * srednicaXZ);
		glVertex3d(x + sin(k) * srednicaXZ, y, z + cos(k) * srednicaXZ);
	}
	glEnd();
	kolo(x, y, z, srednicaXZ, red, green, blue);
	kolo(x, y + wysokoscY, z, srednicaXZ, red, green, blue);
}

void Dron::kolo(GLfloat x, GLfloat y, GLfloat z, GLfloat srednicaXZ, int red, int green, int blue)
{
	glColor3ub(red, green, blue);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(x, y, z);
	for (float k = 0; k < 2 * GL_PI + GL_PI / 12; k += GL_PI / 24)
	{
		glVertex3f(x + cos(k) * srednicaXZ, y, z + sin(k) * srednicaXZ);
	}
	glEnd();
}

void Dron::okrag(GLfloat x, GLfloat y, GLfloat z, GLfloat srednicaXZ, GLfloat gruboscLini, int red, int green, int blue)
{
	glColor3ub(red, green, blue);
	glLineWidth(gruboscLini);
	glBegin(GL_LINE_STRIP);
	for (float k = 0; k < 2 * GL_PI + GL_PI / 12; k += GL_PI / 24)
	{
		glVertex3f(x + cos(k) * srednicaXZ, y, z + sin(k) * srednicaXZ);
	}
	glEnd();
}

void Dron::stozek(GLfloat srodekPodstawyX, GLfloat srodekPodstawyY, GLfloat srodekPodstawyZ, GLfloat srednicaXZ, GLfloat wysokoscY, int red, int green, int blue)
{
	glColor3ub(red, green, blue);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(srodekPodstawyX, srodekPodstawyY + wysokoscY, srodekPodstawyZ);
	for (float k = 0; k < 2 * GL_PI + GL_PI / 12; k += GL_PI / 24)
	{
		glVertex3f(srodekPodstawyX + cos(k) * srednicaXZ, srodekPodstawyY, srodekPodstawyZ + sin(k) * srednicaXZ);
	}
	glEnd();
}

void Dron::romb(GLfloat x, GLfloat y, GLfloat z, GLfloat dlugosc, GLfloat szerokosc, GLfloat wysokosc, float red, float green, float blue)
{
	GLfloat half = dlugosc / 2.0;

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	{
		//dolna sciana
		glColor3f(red, green, blue);
		glBegin(GL_QUADS);
		glVertex3f(x, y, z - half);
		glVertex3f(x + szerokosc, y, z - half);
		glVertex3f(x + szerokosc, y, z + dlugosc);
		glVertex3f(x, y, z + dlugosc);
		glEnd();

		//gorna sciana
		glBegin(GL_QUADS);
		glVertex3f(x, y + wysokosc, z);
		glVertex3f(x + szerokosc, y + wysokosc, z);
		glVertex3f(x + szerokosc, y + wysokosc, z + dlugosc + half);
		glVertex3f(x, y + wysokosc, z + dlugosc + half);
		glEnd();

		/*---------------sciany boczne---------------*/
		glColor3f(red, green, blue);	//ok
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(x, y, z - half);
		glVertex3f(x + szerokosc, y, z - half);
		glVertex3f(x, y + wysokosc, z);
		glVertex3f(x + szerokosc, y + wysokosc, z);
		glEnd();

		glColor3f(red, green, blue);	//ok
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(x, y, z + dlugosc);
		glVertex3f(x + szerokosc, y, z + dlugosc);
		glVertex3f(x, y + wysokosc, z + dlugosc + half);
		glVertex3f(x + szerokosc, y + wysokosc, z + dlugosc + half);
		glEnd();

		glColor3f(red, green, blue);	//ok
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(x, y, z - half);
		glVertex3f(x, y, z);
		glVertex3f(x, y + wysokosc, z);
		glVertex3f(x, y, z + dlugosc);
		glVertex3f(x, y + wysokosc, z + dlugosc);
		glVertex3f(x, y + wysokosc, z + dlugosc + half);
		glEnd();

		glColor3f(red, green, blue);	//ok
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(x + szerokosc, y, z - half);
		glVertex3f(x + szerokosc, y, z);
		glVertex3f(x + szerokosc, y + wysokosc, z);
		glVertex3f(x + szerokosc, y, z + dlugosc);
		glVertex3f(x + szerokosc, y + wysokosc, z + dlugosc);
		glVertex3f(x + szerokosc, y + wysokosc, z + dlugosc + half);
		glEnd();

	}
}

void Dron::ostroslup(GLfloat x, GLfloat y, GLfloat z, GLfloat szerokosc, GLfloat wysokosc, float red, float green, float blue)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	{
		glColor3f(red, green, blue);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(x, y, z);
		glVertex3f(x + szerokosc, y, z);
		glVertex3f(x, y, z + szerokosc);
		glVertex3f(x + szerokosc, y, z + szerokosc);
		glEnd();

		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(x, y, z);
		glVertex3f(x + szerokosc / 2.0, y + wysokosc, z + szerokosc / 2.0);
		glVertex3f(x + szerokosc, y, z);
		glVertex3f(x + szerokosc, y, z + szerokosc);
		glVertex3f(x + szerokosc / 2.0, y + wysokosc, z + szerokosc / 2.0);
		glVertex3f(x, y, z + szerokosc);
		glVertex3f(x, y, z);
		glEnd();
	}
}

void Dron::wiatrak(GLfloat x, GLfloat y, GLfloat z, GLfloat promienLopatki)
{
	//dwie "lopatki" smigla
	glColor3ub(180, 180, 180);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(x, y + 5.0, z);
	glVertex3f(x + cos(GL_PI / 18 * 9) * promienLopatki, y + 5, z + sin(GL_PI / 18 * 9) * promienLopatki); //90 stopni
	glVertex3f(x + cos(GL_PI / 18 * 11) * promienLopatki, y + 5, z + sin(GL_PI / 18 * 11) * promienLopatki); //110
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(x, y + 5.0, z);
	glVertex3f(x + cos(GL_PI / 18 * 27) * promienLopatki, y + 5, z + sin(GL_PI / 18 * 27) * promienLopatki); //270
	glVertex3f(x + cos(GL_PI / 18 * 29) * promienLopatki, y + 5, z + sin(GL_PI / 18 * 29) * promienLopatki); //290
	glEnd();

	//nakretka na smigle
	walecZamkniety(x, y + 4.5, z, 1, 1.5, 0, 0, 0);
	stozek(x, y + 6, z, 0.7, 1.2, 130, 130, 130);

	//czerwone kolo pod smiglem
	walecZamkniety(x, y + 4, z, 1, 0.5, 160, 50, 50);
	walecZamkniety(x, y + 3, z, 2.5, 1, 160, 50, 50);

	//czarne kolo pod czerwonym + polaczenie z uchwytem
	walecZamkniety(x, y + 2, z, 2.5, 1, 0, 0, 0);
	walecZamkniety(x, y + 1, z, 1, 1, 20, 20, 20);
}

void Dron::lacznikSmigloBaza(GLfloat smigloX, GLfloat smigloY, GLfloat smigloZ)
{
	if (smigloX == 0 && smigloY == 0 && smigloZ == 0)
	{
		walecZamkniety(smigloX, smigloY, smigloZ, 3, 1, 70, 110, 110);
		glColor3ub(20, 80, 70);
		glBegin(GL_POLYGON);
		glVertex3f(smigloX + 3, smigloY, smigloZ - 1);
		glVertex3f(smigloX + 12, smigloY - 2, smigloZ + 5);
		glVertex3f(smigloX + 5, smigloY - 2, smigloZ + 12);
		glVertex3f(smigloX - 1, smigloY, smigloZ + 3);
		glEnd();
	}
	else if (smigloX == 40 && smigloY == 0 && smigloZ == 0)
	{
		walecZamkniety(smigloX, smigloY, smigloZ, 3, 1, 70, 110, 110);
		glColor3ub(20, 80, 70);
		glBegin(GL_POLYGON);
		glVertex3f(smigloX + 3, smigloY, smigloZ + 1);
		glVertex3f(smigloX - 5, smigloY - 2, smigloZ + 11);
		glVertex3f(smigloX - 12, smigloY - 2, smigloZ + 5);
		glVertex3f(smigloX - 3, smigloY, smigloZ - 1);
		glEnd();
	}
	else if (smigloX == 40 && smigloY == 0 && smigloZ == 40)
	{
		walecZamkniety(smigloX, smigloY, smigloZ, 3, 1, 70, 110, 110);
		glColor3ub(20, 80, 70);
		glBegin(GL_POLYGON);
		glVertex3f(smigloX + 3, smigloY, smigloZ - 1);
		glVertex3f(smigloX - 5, smigloY - 2, smigloZ - 11);
		glVertex3f(smigloX - 12, smigloY - 2, smigloZ - 5);
		glVertex3f(smigloX - 3, smigloY, smigloZ + 1);
		glEnd();
	}
	else if (smigloX == 0 && smigloY == 0 && smigloZ == 40)
	{
		walecZamkniety(smigloX, smigloY, smigloZ, 3, 1, 70, 110, 110);
		glColor3ub(20, 80, 70);
		glBegin(GL_POLYGON);
		glVertex3f(smigloX + 3, smigloY, smigloZ + 1);
		glVertex3f(smigloX + 12, smigloY - 2, smigloZ - 5);
		glVertex3f(smigloX + 5, smigloY - 2, smigloZ - 12);
		glVertex3f(smigloX - 3, smigloY, smigloZ - 1);
		glEnd();
	}
}

void Dron::kamera(GLfloat x, GLfloat y, GLfloat z)
{
	//gorna sciana
	glColor3f(0, 0, 1);
	glBegin(GL_QUADS);
	glVertex3f(x + 37.0f, y + -6.0f, z + 35.0f);
	glVertex3f(x + 43.0f, y + -6.0f, z + 35.0f);
	glVertex3f(x + 43.0f, y + -6.0f, z + 50.0f);
	glVertex3f(x + 37.0f, y + -6.0f, z + 50.0f);
	glEnd();

	//dolna sciana
	glBegin(GL_QUADS);
	glVertex3f(x + 37.0f, y + -14.0f, z + 35.0f);
	glVertex3f(x + 43.0f, y + -14.0f, z + 35.0f);
	glVertex3f(x + 43.0f, y + -14.0f, z + 50.0f);
	glVertex3f(x + 37.0f, y + -14.0f, z + 50.0f);
	glEnd();

	/*---------------sciany boczne---------------*/
	glColor3f(0.5f, 0.4f, 0.9f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(x + 37.0f, y + -6.0f, z + 35.0f);
	glVertex3f(x + 43.0f, y + -6.0f, z + 35.0f);
	glVertex3f(x + 37.0f, y + -14.0f, z + 35.0f);
	glVertex3f(x + 43.0f, y + -14.0f, z + 35.0f);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(x + 37.0f, y + -6.0f, z + 35.0f);
	glVertex3f(x + 37.0f, y + -6.0f, z + 50.0f);
	glVertex3f(x + 37.0f, y + -14.0f, z + 35.0f);
	glVertex3f(x + 37.0f, y + -14.0f, z + 50.0f);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(x + 37.0f, y + -6.0f, z + 50.0f);
	glVertex3f(x + 43.0f, y + -6.0f, z + 50.0f);
	glVertex3f(x + 37.0f, y + -14.0f, z + 50.0f);
	glVertex3f(x + 43.0f, y + -14.0f, z + 50.0f);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(x + 43.0f, y + -6.0f, z + 35.0f);
	glVertex3f(x + 43.0f, y + -6.0f, z + 50.0f);
	glVertex3f(x + 43.0f, y + -14.0f, z + 35.0f);
	glVertex3f(x + 43.0f, y + -14.0f, z + 50.0f);
	glEnd();

	/*---------------pierwszy walec do kamerki---------------*/
	glColor3f(1.0f, 0.2f, 0.3f);
	glBegin(GL_TRIANGLE_STRIP);
	for (GLfloat k = 0; k < 2 * GL_PI + GL_PI / 12; k += GL_PI / 12)
	{
		glVertex3f(x + 40.0f + cos(k) * 3, y + -10.5f + sin(k) * 3, z + 45.0f);
		glVertex3f(x + 40.0f + cos(k) * 3, y + -10.5f + sin(k) * 3, z + 55.0f);
	}
	glEnd();

	//kolo w pierwszym walcu
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(x + 40.0f, y + -10.5f, z + 55.0f);
	for (GLfloat k = 0; k < 2 * GL_PI + GL_PI / 12; k += GL_PI / 12)
	{
		glVertex3f(x + 40.0f + cos(k) * 3, y + -10.5f + sin(k) * 3, z + 55.0f);
	}
	glEnd();

	/*---------------drugi walec do kamerki---------------*/
	glColor3f(0.6f, 0.0f, 0.4f);
	glBegin(GL_TRIANGLE_STRIP);
	for (GLfloat k = 0; k < 2 * GL_PI + GL_PI / 12; k += GL_PI / 12)
	{
		glVertex3f(x + 40.0f + cos(k) * 2.15, y + -10.5f + sin(k) * 2.15, z + 55.0f);
		glVertex3f(x + 40.0f + cos(k) * 2.15, y + -10.5f + sin(k) * 2.15, z + 59.0f);
	}
	glEnd();

	//kolo w drugim walcu
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(x + 40.0f, y + -10.5f, z + 59.0f);
	for (GLfloat k = 0; k < 2 * GL_PI + GL_PI / 12; k += GL_PI / 12)
	{
		glVertex3f(x + 40.0f + cos(k) * 2.15, y + -10.5f + sin(k) * 2.15, z + 59.0f);
	}
	glEnd();

	/*---------------trzeci walec do kamerki---------------*/
	glColor3f(0.9f, 0.0f, 0.2f);
	glBegin(GL_TRIANGLE_STRIP);
	for (GLfloat k = 0; k < 2 * GL_PI + GL_PI / 12; k += GL_PI / 12)
	{
		glVertex3f(x + 40.0f + cos(k) * 1.5, y + -10.5f + sin(k) * 1.5, z + 59.0f);
		glVertex3f(x + 40.0f + cos(k) * 1.5, y + -10.5f + sin(k) * 1.5, z + 62.0f);
	}
	glEnd();

	//kolo w trzecim walcu
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(x + 40.0f, y + -10.5f, z + 62.0f);
	for (GLfloat k = 0; k < 2 * GL_PI + GL_PI / 12; k += GL_PI / 12)
	{
		glVertex3f(x + 40.0f + cos(k) * 1.5, y + -10.5f + sin(k) * 1.5, z + 62.0f);
	}
	glEnd();
}

void Dron::pierscien(GLfloat x, GLfloat y, GLfloat z, GLdouble r, GLdouble h)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	{
		GLfloat a, b;
		glColor3f(0.0f, 0.0f, 0.5f);
		glBegin(GL_TRIANGLE_STRIP);
		for (GLfloat k = 0; k <= 2 * GL_PI; k += GL_PI / 16.0)
		{
			a = r* sin(k);
			b = r* cos(k);
			glVertex3d(x + a, y + 0, z + b);
			a *= 1.2;
			b *= 1.2;
			glVertex3d(x + a, y + 0, z + b);
		}
		glEnd();

		glBegin(GL_TRIANGLE_STRIP);
		for (GLfloat k = 0; k <= 2 * GL_PI; k += GL_PI / 16.0)
		{
			a = r* sin(k);
			b = r* cos(k);
			glVertex3d(x + a, y + h, z + b);
			a *= 1.2;
			b *= 1.2;
			glVertex3d(x + a, y + h, z + b);
		}
		glEnd();

		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_TRIANGLE_STRIP);
		for (GLfloat k = 0; k <= 2 * GL_PI; k += GL_PI / 16.0)
		{
			a = r* sin(k);
			b = r* cos(k);
			glVertex3d(x + a, y + 0, z + b);
			glVertex3d(x + a, y + h, z + b);
		}
		glEnd();

		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_TRIANGLE_STRIP);
		for (GLfloat k = 0; k <= 2 * GL_PI; k += GL_PI / 16.0)
		{
			a = r* sin(k);
			b = r* cos(k);
			a *= 1.2;
			b *= 1.2;
			glVertex3d(x + a, y + 0, z + b);
			glVertex3d(x + a, y + h, z + b);
		}
		glEnd();
	}
}

void Dron::krzyz(GLfloat x, GLfloat y, GLfloat z, GLfloat r)
{
	GLfloat a, b;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	{
		//walec wzdluz osi x
		glColor3f(0.0f, 0.5f, 0.5f);
		glBegin(GL_TRIANGLE_STRIP);
		for (GLfloat k = 0; k < 2 * GL_PI; k += GL_PI / 16.0)
		{
			a = r *sin(k);
			b = r *cos(k);
			glVertex3f(x - 20, y + b, z + a);
			glVertex3f(x + 20, y + b, z + a);
		}
		glEnd();

		//kolo na jednym zakonczeniu walca
		glColor3f(0.0f, 0.5f, 0.5f);
		glBegin(GL_TRIANGLE_FAN);
		for (GLfloat k = 0; k < 2 * GL_PI; k += GL_PI / 16.0)
		{
			a = r *sin(k);
			b = r *cos(k);
			glVertex3f(x - 20, y + b, z + a);
		}
		glEnd();

		//kolo na drugim zakonczeniu walca
		glColor3f(0.0f, 0.5f, 0.5f);
		glBegin(GL_TRIANGLE_FAN);
		for (GLfloat k = 0; k < 2 * GL_PI; k += GL_PI / 16.0)
		{
			a = r *sin(k);
			b = r *cos(k);
			glVertex3f(x + 20, y + b, z + a);
		}
		glEnd();

		//walec wzdluz osi z
		glColor3f(0.0f, 0.5f, 0.5f);
		glBegin(GL_TRIANGLE_STRIP);
		for (GLfloat k = 0; k < 2 * GL_PI; k += GL_PI / 16.0)
		{
			a = r *sin(k);
			b = r *cos(k);
			glVertex3f(x + a, y + b, z - 20);
			glVertex3f(x + a, y + b, z + 20);
		}
		glEnd();

		//kolo na jednym zakonczeniu walca
		glColor3f(0.0f, 0.5f, 0.5f);
		glBegin(GL_TRIANGLE_FAN);
		for (GLfloat k = 0; k < 2 * GL_PI; k += GL_PI / 16.0)
		{
			a = r *sin(k);
			b = r *cos(k);
			glVertex3f(x + a, y + b, z - 20);
		}
		glEnd();

		//kolo na drugim zakonczeniu walca
		glColor3f(0.0f, 0.5f, 0.5f);
		glBegin(GL_TRIANGLE_FAN);
		for (GLfloat k = 0; k < 2 * GL_PI; k += GL_PI / 16.0)
		{
			a = r *sin(k);
			b = r *cos(k);
			glVertex3f(x + a, y + b, z + 20);
		}
		glEnd();
	}
}
