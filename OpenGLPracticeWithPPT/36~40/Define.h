#pragma once

#include <Windows.h>
#include "./GL/glew.h"
#include "./GL/glut.h"
#include "./GL/wglew.h"
#include <iostream>
#include <vector>
#include <atlstr.h>

#include "CCameraManager.h"
#include "CRenderManager.h"
#include "CFactoryManagerr.h"

#include "Matrix.h"

#pragma comment(lib, "DLL.lib")
#pragma comment(lib, "glew32.lib")

using namespace std;


static unsigned const int WINDOW_WIDTH = 1280;
static unsigned const int WINDOW_HEIGHT = 720;
static unsigned const int WINDOW_INIT_X = 300;
static unsigned const int WINDOW_INIT_Y = 100;
static unsigned const int TAB_WINDOW_INIT_Y = WINDOW_INIT_Y - 31;

static const float PERSPEVTIVE_FOVY = 45.0f;
static const float PERSPEVTIVE_NEAR = 0.12f;
static const float PERSPEVTIVE_FAR = 512.0f;

static const float CAMERA_ANGLE_IN = 2.0f;
static const float CAMERA_SPEED = 10.0f;
static const float CAMERA_INIT_Z = 20.0f;

static const float OBJECT_SPEED = 1.0f;


#define CAMERAMANAGER CCameraManager::GetInstance()
#define RENDERMANAGER CRenderManager::GetInstance()
#define FACTORYMANAGER CFactoryManager::GetInstance()


