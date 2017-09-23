#ifndef DEFINE_H
#define DEFINE_H

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <gl/glut.h>
#include <time.h>
#include <Windows.h>

#include "CFactory.h"
#include "Enum.h"

using namespace std;

typedef int DATA_TYPE;

const float RGB = 255.0f;

const float WINDOW_SIZE_WIDTH = 800.0f;
const float WINDOW_SIZE_HEIGHT = 600.0f;

const int MAX_CIRCLE_SPEED = 5;

const int SPEED_UP = 1, SPEED_DOWN = -1;

struct Pos
{
	DATA_TYPE x, y;
	Pos()
	{
		x = 0, y = 0;
	}

	Pos(DATA_TYPE x, DATA_TYPE y) : x(x), y(y) {};
};

struct Color
{
	float R, G, B;

	Color()
	{
		R = 255.0f, G = 0.0f, B = 0.0f;
	}

	Color(float R, float G, float B) : R(R), G(G), B(B) {};

};

#define FACTORYMANAGER CFactory::GetInstance()

#endif