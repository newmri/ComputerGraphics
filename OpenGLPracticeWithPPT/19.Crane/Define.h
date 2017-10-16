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

const float CRANE_SPEED = 1.0f;
const float BOTTOM_SIZE = 7.0f;
const float BODY_SIZE = 5.0f;
const float ARM_SIZE = 3.0f;

const float FLOOR_SIZE = 10.0f;

const float CAMERA_ANGLE_IN = 2.0f;
const float CAMERA_SPEED = 1.0f;

enum { X, Y, Z };

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