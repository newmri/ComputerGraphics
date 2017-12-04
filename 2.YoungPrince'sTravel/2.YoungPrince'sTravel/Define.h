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
#include "CTextureManager.h"
#include "CRenderManager.h"

#include "Enum.h"
#include "Matrix.h"

#pragma comment(lib,"DLL.lib")

using namespace std;

typedef float DATA_TYPE;

static const float RGB = 255.0f;

static const float WINDOW_WIDTH = 800.0f;
static const float WINDOW_HEIGHT = 600.0f;

static const float FLOOR_SIZE = 10.0f;
static const float HEXAHEDRON_TREE_SIZE = 5.0f;
static const float REAL_WINDOW_WIDTH = 60.0f;
static const float WINDOW_DEPTH = 200.0f;
static const float REAL_WINDOW_DEPTH = WINDOW_DEPTH / 2.0f;
static const float GAP_OF_END = REAL_WINDOW_WIDTH / 4.0f;

static const float PERSPEVTIVE_FOVY = 45.0f;
static const float PERSPEVTIVE_NEAR = 0.12f;
static const float PERSPEVTIVE_FAR = 512.0f;

static const double PI = 3.141592654;
static const double TWOPI = 6.283185308;
static const double PID2 = 1.570796326794897;

static const float CUBE_SIZE = 50.0f;


static const float CAMERA_ANGLE_IN = 2.0f;
static const float CAMERA_SPEED = 1.0f;

static const float EARTH_RAD = 5.0f;

static const int HOUSE_FRONT = 8;
static const int HOUSE_SIDE = 9;
static const int HOUSE_RAD = 2;

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
#define FACTORYMANAGER CFactory::GetInstance()
#define TEXTUREMANAGER CTextureManager::GetInstance()
#define RENDERMANAGER CRenderManager::GetInstance()
#endif