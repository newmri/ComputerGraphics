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
const int SPEED = 3;
const int MAX_MOVE = 6;
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
	bool GetStoped() { return (m_moveCnt == MAX_MOVE); }
public:
	void ChangeColor();
	void ChangeShape();
	void ChangeSpeed(const int speed);

public:
	void Move();

public:
	void Draw();

public:
	CRect()
	{
		m_width = (rand() % MAX_RECT_SIZE) + 10;
		m_height = (rand() % MAX_RECT_SIZE) + 10;
		m_changeShape = false;
		this->SetPos(rand() % static_cast<DATA_TYPE>(WINDOW_SIZE_WIDTH),
			rand() % static_cast<DATA_TYPE>(WINDOW_SIZE_HEIGHT));

		m_speed = SPEED;
		if (rand() % 2) {
			m_dx = -1 * m_speed;
			m_dy = m_speed;
		}
		else {
			m_dx = m_speed;
			m_dy = -1 * m_speed;
		}
		m_moveHorizontal = false;
		m_moveCnt = 0;
	}
private:
	Pos m_pos;
	DATA_TYPE m_width, m_height;
	Rgb m_rgb;
	int m_dx, m_dy;
	int m_speed;
	bool m_changeShape;
	bool m_moveHorizontal;
	int m_moveCnt;
};