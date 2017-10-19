#pragma once
#include <gl/glut.h>
#include <Windows.h>
#include <iostream>
#include <vector>
#include <memory>
#include <math.h>

#include "CObject.h"
#include "CRect.h"
#include "CMouseManager.h"

#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")

using namespace std;

const float WINDOWS_WIDTH = 800.0f;
const float WINDOWS_HEIGHT = 600.0f;

const float RECT_SIZE = 0.3f;


#define MOUSEMANAGER CMouseManager::GetInstance()
#define END_OF_LINE MOUSEMANAGER->GetPosList().size() - 1