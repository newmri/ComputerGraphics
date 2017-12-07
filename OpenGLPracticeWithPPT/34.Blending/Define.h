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

static const float REAL_WINDOW_WIDTH = 60.0f;
static const float WINDOW_DEPTH = 200.0f;
static const float REAL_WINDOW_DEPTH = WINDOW_DEPTH / 2.0f;

const float BIG_TRIANGLE_SIZE = 0.3f;
const float SMALL_TRIANGLE_SIZE = 0.05f;

const int SPEED = 5;
const int SPEED_UP = 1, SPEED_DOWN = -1;

const float PIE = 3.141592;


struct Pos
{
	DATA_TYPE x, y, z;
	Pos()
	{
		x = 0.0f, y = 0.0f, z = 0.0f;
	}

	Pos(DATA_TYPE x, DATA_TYPE y, DATA_TYPE z) : x(x), y(y), z(z) {};
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