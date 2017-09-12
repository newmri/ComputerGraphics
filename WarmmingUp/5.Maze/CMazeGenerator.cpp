#include "CMazeGenerator.h"

void CMazeGenerator::Init()
{
	for (int y = 0; y < m_height; ++y) {
		for (int x = 0; x < m_width; ++x)  m_maze[x][y] = OBJECT::WALL;
	}
	m_xStart = 0;
	m_yStart = 0;
	m_xExit = m_width - 1;
	m_yExit = m_height - 1;

	m_x = 1, m_y = 1;
	m_sp = 0;
	m_minPath = 100000;
	m_exsitExit = false;

	// Create wall on even number
	for (m_x = 1; m_x < m_width; ++m_x) {
		for (m_y = 1; m_y < m_height; ++m_y) {
			if(m_y != m_height - 1 && m_x != m_width - 1)
			if (m_x % 2 != 0 || m_y % 2 != 0) m_maze[m_x][m_y] = OBJECT::PATH;

		}
	}
	m_maze[0][1] = OBJECT::PATH;
	this->MakeLeftWall();
	this->MakeWall();
	while (!FindRoute(m_xStart, m_yStart)) Init();
	SetShortedPath();
}


void CMazeGenerator::MakeLeftWall()
{
	int wallDir{};
	m_y = 2;
	for (m_x = 2; m_x < m_width; m_x += 2) {
		wallDir = rand() % DIRECTION::END;
		switch (wallDir) {
		case DIRECTION::EAST:
			m_maze[m_x][m_y + 1] = OBJECT::WALL;
			break;
		case DIRECTION::WEST:
			m_maze[m_x][m_y - 1] = OBJECT::WALL;
			break;
		case DIRECTION::SOUTH:
			m_maze[m_x + 1][m_y] = OBJECT::WALL;
			break;
		case DIRECTION::NORTH:
			m_maze[m_x - 1][m_y] = OBJECT::WALL;
			break;
		default:
			break;
		}
	}
}

void CMazeGenerator::MakeWall()
{
	int wallDir{};

	for (m_y = 4; m_y < m_height; m_y += 2) {
		for (m_x = 2; m_x < m_width; m_x += 2) {
			wallDir = rand() % 3;
			switch (wallDir) {
			case DIRECTION::EAST: 
				m_maze[m_x][m_y + 1] = OBJECT::WALL;
				break;
			case DIRECTION::SOUTH: 
				m_maze[m_x + 1][m_y] = OBJECT::WALL;
				break;
			case DIRECTION::NORTH: 
				m_maze[m_x - 1][m_y] = OBJECT::WALL;
				break;
			default:
				break;
			}
		}
	}

	m_maze[m_xStart][m_yStart] = OBJECT::PATH;
	m_maze[m_xExit][m_yExit] = OBJECT::PATH;
	m_maze[m_xExit][m_yExit - 1] = OBJECT::PATH;

	if (m_width % 2 == 0) {
		m_maze[m_xExit][m_yExit] = OBJECT::PATH;
		m_maze[m_xExit - 1][m_yExit -1] = OBJECT::PATH;
	}
}


bool CMazeGenerator::FindRoute(const int xCurr, const int yCurr)
{

	// Save position past
	m_maze[xCurr][yCurr] = OBJECT::WALL; // Change to wall past
	m_xVisit[m_sp] = xCurr;
	m_yVisit[m_sp] = yCurr;
	m_sp++;
	if (xCurr == m_xExit && yCurr == m_yExit) { // Got to exit
		
		if (m_sp < m_minPath) {
			for (int i = 0; i < m_sp; ++i) {
				m_xShortPath[i] = m_xVisit[i];
				m_yShortPath[i] = m_yVisit[i];
				m_minPath = m_sp;
			}
		}
		
		m_exsitExit = true;
	}
	if (!m_exsitExit) {
		if (m_maze[xCurr][yCurr + 1] == OBJECT::PATH) FindRoute(xCurr, yCurr + 1); // East
		if (!m_exsitExit)
		if (m_maze[xCurr + 1][yCurr] == OBJECT::PATH) FindRoute(xCurr + 1, yCurr); // South
		if (!m_exsitExit)
		if (m_maze[xCurr][yCurr - 1] == OBJECT::PATH) FindRoute(xCurr, yCurr - 1); // West
		if (!m_exsitExit)
		if (m_maze[xCurr - 1][yCurr] == OBJECT::PATH) FindRoute(xCurr - 1, yCurr); // North
	}
	m_sp--; // Pop

	//cout << "X cur: " << xCurr << "Y cur: " << yCurr << endl;
	m_maze[xCurr][yCurr] = OBJECT::PATH;

	return m_exsitExit;
}

void CMazeGenerator::SetShortedPath()
{
	for (int i = 0; i < m_minPath; i++) m_maze[m_xShortPath[i]][m_yShortPath[i]] = OBJECT::SHORTEST_PATH;
}

void CMazeGenerator::Draw()
{

	for (m_x = 0; m_x < m_width; ++m_x) {
		for (m_y = 0; m_y < m_height; ++m_y) {
			if (m_maze[m_x][m_y] == OBJECT::WALL) cout << "+ ";
			else if (m_maze[m_x][m_y] == OBJECT::PATH) cout<<"  "; 
			else if (m_maze[m_x][m_y] == OBJECT::SHORTEST_PATH) cout<<". "; 
		}
		cout << endl;
	}
	cout << endl;

}

void CMazeGenerator::DeleteMemory()
{
	//for (int i = 0; i < m_width; ++i) delete[] m_maze[i];
	//delete[] m_maze;

	//m_maze = nullptr;
}