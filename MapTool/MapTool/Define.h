#pragma once

#include <Windows.h>
#include <CommCtrl.h>
#include <atlimage.h>
//#include <gl/glut.h>
#include <gl/freeglut.h>
#include <iostream>

#include "resource.h"
#include "CMouseManager.h"
#include "CCameraManager.h"
#include "CRenderManager.h"

#include "Matrix.h"

#pragma comment(lib,"comctl32.lib")
#pragma comment(lib,"DLL.lib")
#pragma comment(lib,"freeglut.lib")

using namespace std;

enum OBJECT_SELECT_TYPE { BRICK, OBSTACLE, END };

static unsigned const int WINDOW_WIDTH = 1280;
static unsigned const int WINDOW_HEIGHT = 720;
static unsigned const int WINDOW_INIT_X = 300;
static unsigned const int WINDOW_INIT_Y = 100;
static unsigned const int TAB_WINDOW_INIT_Y = WINDOW_INIT_Y - 31;
static const float PERSPEVTIVE_FOVY = 10.0f;
static const float PERSPEVTIVE_NEAR = 0.125f;
static const float PERSPEVTIVE_FAR = 512.0f;

static const float CAMERA_ANGLE_IN = 2.0f;
static const float CAMERA_SPEED = 1.0f;

//CString g_moduleDirectory, g_errorLog;

#define MOUSEMANAGER CMouseManager::GetInstance()
#define CAMERAMANAGER CCameraManager::GetInstance()
#define RENDERMANAGER CRenderManager::GetInstance()




