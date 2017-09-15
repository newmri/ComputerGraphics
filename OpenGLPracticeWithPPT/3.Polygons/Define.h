#ifndef DEFINE_H
#define DEFINE_H

#include <iostream>
#include <gl/glut.h>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <memory>

#include "Enum.h"
#include "CFactory.h"

using namespace std;

struct Rgb
{
	float R, G, B;

	Rgb()
	{
		R = 255.0f, G = 0.0f, B = 0.0f;
	}
};


const float RGB = 255.0f;

const float WINDOW_WIDTH = 800.0f;
const float WINDOW_HEIGHT = 600.0f;

const float CROSS_DRAW_X = WINDOW_WIDTH / 3.0f;
const float CROSS_DRAW_Y = WINDOW_HEIGHT / 3.0f;

const int CROSS_X_NUM = 3;
const int CROSS_Y_NUM = 3;

#define FACTPRYMANAGER CFactory::GetInstance()

#endif