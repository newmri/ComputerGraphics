#pragma once
#include <gl/glut.h>
#include <Windows.h>
#include <iostream>

#include "CObject.h"
#include "CMouseManager.h"

#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")

using namespace std;

const float WINDOWS_WIDTH = 800.0f;
const float WINDOWS_HEIGHT = 600.0f;


#define MOUSEMANAGER CMouseManager::GetInstance()