#pragma once

#include <time.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

const int HEIGHT = 50;
const int WIDTH = 50;

enum OBJECT { WALL, PATH, SHORTEST_PATH };
enum DIRECTION { NORTH, EAST, SOUTH, WEST, END };

class CMazeGenerator
{
public:
	friend void operator>>(istream &is, CMazeGenerator& maze)
	{
		int size[2];
		is >> size[0] >> size[1];

		maze.SetWidth(size[0]);
		maze.SetHeight(size[1]);
	}


public:
	void SetWidth(const int width) { m_width = width; }
	void SetHeight(const int height)
	{
		m_height = height;
		m_xShortPath = new int[m_width * m_height];
		m_yShortPath = new int[m_width * m_height];
		m_xVisit = new int[m_width * m_height];
		m_yVisit = new int[m_width * m_height];
	}
public:
	void Draw();

public:
	void Init();
	void DeleteMemory();

public:
	void MakeLeftWall();
	void MakeWall();

public:
	bool FindRoute(const int xCurr, const int yCurr);
	void SetShortedPath();
public:
	CMazeGenerator()
	{
		srand((unsigned)time(NULL));

		m_height = HEIGHT;
		m_width = WIDTH;
		m_xVisit = nullptr;
		m_yVisit = nullptr;
		m_xShortPath = nullptr;
		m_yShortPath = nullptr;
	}
	~CMazeGenerator()
	{
		delete[] m_xShortPath;
		delete[] m_yShortPath;
		delete[] m_xVisit;
		delete[] m_yVisit;
	}
private:
	OBJECT m_maze[HEIGHT][WIDTH];
	int m_height, m_width;
	int m_x, m_y;
	int m_xStart, m_yStart;
	int m_xExit, m_yExit;
	int* m_xVisit;
	int* m_yVisit;
	int m_sp;
	int m_minPath;
	int* m_xShortPath;
	int* m_yShortPath;
	bool m_exsitExit;
};