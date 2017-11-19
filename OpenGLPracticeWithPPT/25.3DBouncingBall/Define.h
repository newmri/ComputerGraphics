#ifndef DEFINE_H
#define DEFINE_H

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <gl/glut.h>
#include <time.h>
#include <Windows.h>
#include <memory>

#include "CCameraManager.h"
#include "CFactory.h"
#include "Enum.h"

using namespace std;

typedef float DATA_TYPE;

const float RGB = 255.0f;

const float WINDOW_WIDTH = 800.0f;
const float WINDOW_HEIGHT = 600.0f;
static const float REAL_WINDOW_WIDTH = 60.0f;
static const float WINDOW_DEPTH = 150.0f;

const float PIE = 3.141592;
const float CUBE_RAD = 30.0f;
static const float BALL_RAD = 2.0f;
static const float BALL_SPEED = 1.0f;


const float CAMERA_ANGLE_IN = 2.0f;
const float CAMERA_SPEED = 1.0f;

const float MAX_DEGREE = 360.0f;



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
#define FACTORYMANAGER CFactory::GetInstance()

#endif