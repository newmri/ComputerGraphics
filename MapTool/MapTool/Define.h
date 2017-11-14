#pragma once

#include <Windows.h>
#include <CommCtrl.h>
#include <atlimage.h>
#include <gl/glut.h>
#include <iostream>

#include "resource.h"

#pragma comment(lib,"comctl32.lib")

using namespace std;

enum OBJECT_SELECT_TYPE { BRICK, OBSTACLE, END };

static unsigned const int WINDOW_WIDTH = 1280;
static unsigned const int WINDOW_HEIGHT = 720;
static unsigned const int WINDOW_INIT_X = 300;
static unsigned const int WINDOW_INIT_Y = 100;
static unsigned const int REAL_WINDOW_FOVY = 60;
static unsigned const int WINDOW_DEPTH = 150;