#pragma once

#include <Windows.h>
#include <CommCtrl.h>
#include <atlimage.h>
//#include <gl/glut.h>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <iostream>
#include <vector>

#include "resource.h"
#include "CCameraManager.h"
#include "CRenderManager.h"
#include "CDialogManager.h"
#include "CFileManager.h"
#include "Matrix.h"

#pragma comment(lib,"comctl32.lib")
#pragma comment(lib,"DLL.lib")
#pragma comment(lib,"freeglut.lib")

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
static const float CAMERA_SPEED = 1.0f;
static const float CAMERA_INIT_Z = 20.0f;

static const float OBJECT_SPEED = 1.0f;
//CString g_moduleDirectory, g_errorLog;

#define CAMERAMANAGER CCameraManager::GetInstance()
#define RENDERMANAGER CRenderManager::GetInstance()
#define DIALOGMANAGER CDialogManager::GetInstance()
#define FILEMANAGER CFileManager::GetInstance()


