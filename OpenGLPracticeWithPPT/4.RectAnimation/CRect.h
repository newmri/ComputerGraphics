#pragma once

#include <time.h>
#include <stdlib.h>
#include <queue>
#include <iostream>
#include <gl/glut.h>

using namespace std;

typedef int DATA_TYPE;

const float RGB = 255.0f;

const float WINDOW_SIZE_WIDTH = 800.0f;
const float WINDOW_SIZE_HEIGHT = 600.0f;

const float TOP = WINDOW_SIZE_HEIGHT / 2;
const float BOTTOM = (WINDOW_SIZE_HEIGHT / 2) * -1;
const float LEFT = (WINDOW_SIZE_WIDTH / 2) * -1;
const float RIGHT = WINDOW_SIZE_WIDTH / 2;

const int MAX_RECT_SIZE = 100;
struct Pos
{
	DATA_TYPE left, top, right, bottom;
	Pos()
	{
		left = 0, top = 0, right = 0, bottom = 0;
	}
};

struct Rgb
{
	float R, G, B;

	Rgb()
	{
		R = 255.0f, G = 0.0f, B = 0.0f;
	}
};

class CRect
{

public:
	void SetPos(DATA_TYPE x, DATA_TYPE y);

public:
	void ChangeColor();
	void ChangeShape();

public:
	void Draw();

public:
	CRect()
	{
		m_width = (rand() % MAX_RECT_SIZE) + 10;
		m_height = (rand() % MAX_RECT_SIZE) + 10;
		m_changeShape = false;
	}
private:
	Pos m_pos;
	DATA_TYPE m_width, m_height;
	Rgb m_rgb;
	bool m_changeShape;
};