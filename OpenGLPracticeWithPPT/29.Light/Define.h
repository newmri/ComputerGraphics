#ifndef DEFINE_H
#define DEFINE_H

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <gl/glut.h>
#include <time.h>
#include <Windows.h>

#include "CFactory.h"
#include "CCameraManager.h"
#include "Enum.h"

using namespace std;

typedef float DATA_TYPE;

const float RGB = 255.0f;

const float WINDOW_WIDTH = 800.0f;
const float WINDOW_HEIGHT = 600.0f;

static const float FLOOR_SIZE = 10.0f;
static const float HEXAHEDRON_TREE_SIZE = 5.0f;
static const float REAL_WINDOW_WIDTH = 60.0f;
static const float WINDOW_DEPTH = 200.0f;
static const float REAL_WINDOW_DEPTH = WINDOW_DEPTH / 2.0f;
static const float GAP_OF_END = REAL_WINDOW_WIDTH / 4.0f;

static const float TRACK_RAD = 20.0f;
static const float MOON_TRACK_RAD = 10.0f;
const float MOON_RAD = 1.0f;
const float PLANET_RAD = 4.0f;

static const float SPEED = 0.1f;
const int SPEED_UP = 1, SPEED_DOWN = -1;

const float PIE = 3.141592;

const float CRANE_SPEED = 1.0f;


const float CAMERA_ANGLE_IN = 2.0f;
const float CAMERA_SPEED = 1.0f;

enum { X, Y, Z };

static const Vector3 FLOOR_SCALE{ 10.0f, 3.0f, 3.0f };
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