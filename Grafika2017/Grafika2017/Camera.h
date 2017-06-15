#pragma once
#include<glut.h>
#include<iostream>
#include<glm.hpp>



void processNormalKeys(unsigned char key, int x, int y);
void pressKey(int key, int x, int y);
void releaseKey(int key, int x, int y);
void mouseButton(int button, int state, int x, int y);
void mouseMove(int x, int y);
void computePos(float deltaMove);
void computeDir(float deltaAngle);
