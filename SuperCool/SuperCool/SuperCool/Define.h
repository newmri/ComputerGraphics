#pragma once

#include <Windows.h>
#include "./GL/glew.h"
#include "./GL/glut.h"
#include "./GL/wglew.h"
#include <iostream>
#include <vector>
#include <atlstr.h>
#include <time.h>

#include "CCameraManager.h"
#include "CRenderManager.h"
#include "CFileManager.h"
#include "CFactoryManagerr.h"
#include "CTextureManager.h"
#include "CSoundManager.h"

#include "./DLL/Matrix.h"

#pragma comment(lib, "./lib/DLL.lib")
#pragma comment(lib, "./lib/glew32.lib")

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

static const float FALL_SPEED = CAMERA_SPEED / 3.0f;
static const float JUMP_MULTI = 20.0f;
static const float OBJECT_SPEED = 1.0f;

static const int ENEMY_SIZE = 5;
static const float ENEMY_SPEED = 0.8f;
static const float ENEMY_DOWN_SPEED = ENEMY_SPEED / 1.5f;

static const double PI = 3.141592654;
static const double TWOPI = 6.283185308;
static const double PID2 = 1.570796326794897;

static const float BULLET_RAD = 0.1f;
static const float BULLET_SPEED = 100.0f;

static const float ITEM_RAD = 1.0f;
static const int ITEM_SPEED = 10;

static const int SPEED_UP_TIME = 3000;
static const int SPEED_DOWN_TIME = 2000;
static const int FROZEN_TIME = 1500;

static int FPS_RATE = 60;

static const int STAGE1_TIME = 60000;

static const int PARTICLE_NUM = 100;
static const float PARTICLE_SPEED = 100.0f;
static const int PARTICLE_TIME = 1500;

#define CAMERAMANAGER CCameraManager::GetInstance()
#define RENDERMANAGER CRenderManager::GetInstance()
#define FILEMANAGER CFileManager::GetInstance()
#define FACTORYMANAGER CFactoryManager::GetInstance()
#define TEXTUREMANAGER CTextureManager::GetInstance()
#define SOUNDMANAGER CSoundManager::GetInstance()
