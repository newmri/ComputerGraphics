#ifndef DEFINE_H
#define DEFINE_H

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <gl/glut.h>
#include <time.h>

#include "CFactory.h"
#include "Enum.h"

using namespace std;

typedef int DATA_TYPE;

const float RGB = 255.0f;

const float WINDOW_SIZE_WIDTH = 800.0f;
const float WINDOW_SIZE_HEIGHT = 600.0f;

const float TOP = WINDOW_SIZE_HEIGHT / 2;
const float BOTTOM = (WINDOW_SIZE_HEIGHT / 2) * -1;
const float LEFT = (WINDOW_SIZE_WIDTH / 2) * -1;
const float RIGHT = WINDOW_SIZE_WIDTH / 2;

const int MAX_RECT_SIZE = 100;
const int SPEED = 4;

const int SPEED_UP = 1, SPEED_DOWN = -1;

struct RectPos
{
	DATA_TYPE left, top, right, bottom;
	RectPos()
	{
		left = 0, top = 0, right = 0, bottom = 0;
	}
};

struct Pos
{
	DATA_TYPE x, y;
	Pos()
	{
		x = 0, y = 0;
	}
	Pos(DATA_TYPE ax, DATA_TYPE ay)
	{
		x = ax, y = ay;
	}
};

struct Rgb
{
	float R, G, B;

	Rgb()
	{
		R = 255.0f, G = 0.0f, B = 0.0f;
	}
};

#define FACTORYMANAGER CFactory::GetInstance()
#define EFFECTMANAGER EffectManager::GetInstance()
#endif