#ifndef DEFINE_H
#define DEFINE_H

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <gl/glut.h>
#include <time.h>
#include <Windows.h>

#include "CCameraManager.h"

#include "Enum.h"

using namespace std;

typedef float DATA_TYPE;

const float RGB = 255.0f;

const float WINDOW_WIDTH = 800.0f;
const float WINDOW_HEIGHT = 600.0f;

const float BIG_TRIANGLE_SIZE = 0.3f;
const float SMALL_TRIANGLE_SIZE = 0.05f;

const int SPEED = 5;
const int SPEED_UP = 1, SPEED_DOWN = -1;

const float PIE = 3.141592;

const float COORDINATES_SIZE = 1.0f;

const float SUN_RAD = 5.0f;
const float PLANET_RAD = 4.0f;
const float MOON_RAD = 1.0f;

const float TRACK_RAD = 15.0f;
const float MOON_TRACK_RAD = PLANET_RAD * 2.0f;

const float WHITE_SPEED = 1.0f;
const float YELLOW_SPEED = 2.0f;
const float BLUE_SPEED = 3.0f;

const float MOON_SPEED = 1.5f;

const float CAMERA_ANGLE_IN = 2.0f;
const float CAMERA_SPEED = 1.0f;

struct Color
{
	float R, G, B;

	Color()
	{
		R = 255.0f, G = 0.0f, B = 0.0f;
	}

	Color(float R, float G, float B) : R(R), G(G), B(B) {};

};



#define CAMERAMANAGER CCameraManager::GetInstance()

#endif