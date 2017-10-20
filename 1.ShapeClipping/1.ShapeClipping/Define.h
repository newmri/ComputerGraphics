#pragma once
#include <gl/glut.h>
#include <Windows.h>
#include <iostream>
#include <vector>
#include <memory>
#include <random>

#include "CObject.h"
#include "CRect.h"
#include "CMouseManager.h"
#include "CPolygon.h"

#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")

using namespace std;

const float WINDOWS_WIDTH = 800.0f;
const float WINDOWS_HEIGHT = 600.0f;



const float SPEED = 0.02f;

const float WATER_DEVIDE = 2.0f;
const float MAX_WATER_H = 1.2;
const float WATER_INC = 0.01f;

#define MOUSEMANAGER CMouseManager::GetInstance()
#define END_OF_LINE MOUSEMANAGER->GetPosList().size() - 1