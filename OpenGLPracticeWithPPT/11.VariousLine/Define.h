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

typedef float DATA_TYPE;

const float RGB = 255.0f;

const float WINDOW_WIDTH = 800.0f;
const float WINDOW_HEIGHT = 600.0f;

const float LEFT = -(WINDOW_WIDTH / 2.0f);
const float RIGHT = (WINDOW_WIDTH / 2.0f);
const float TOP = (WINDOW_HEIGHT / 2.0f);
const float BOTTOM = -(WINDOW_HEIGHT / 2.0f);

const int MAX_CIRCLE_SPEED = 5;

const int SPEED_UP = 1, SPEED_DOWN = -1;

const float PIE = 3.141592;

struct Pos
{
	DATA_TYPE x, y;
	Pos()
	{
		x = 0.0f, y = 0.0f;
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