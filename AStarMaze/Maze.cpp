/*
	Programmed by Xiaoqin Du, 383979583@qq.com
	School of Math and Computer Science, 
	Wuhan Textile University
*/

#include "stdafx.h"

#include "maze.h"

MyObjects::Maze::Maze(int width, int height)
{
	m_nWidth = width + 2;
	m_nHeight = height + 2;

	m_ppMaze = new short*[m_nHeight];
	for (int row = 0; row < m_nHeight; row++)
		m_ppMaze[row] = new short[m_nWidth];

	for (int row = 0; row < m_nHeight; row++)
		for (int col = 0; col < m_nWidth; col++)
			m_ppMaze[row][col] = PASS_VALUE;

	for (int row = 0; row < m_nHeight; row++)
		m_ppMaze[row][0] = m_ppMaze[row][m_nWidth-1] = OBSTACLE_VALUE;

	for (int col = 0; col < m_nWidth; col++)
		m_ppMaze[0][col] = m_ppMaze[m_nHeight-1][col] = OBSTACLE_VALUE;

	srand((unsigned)time(NULL));

	int max_obstacles = (m_nWidth * m_nHeight) /4;
	for (int i = 0; i < max_obstacles; i++) {
		int x = rand() % m_nWidth;
		int y = rand() % m_nHeight;
		m_ppMaze[y][x] = OBSTACLE_VALUE;
	}

	m_posStartLoc.x = 1;
	m_posStartLoc.y = 1;
	m_ppMaze[m_posStartLoc.y][m_posStartLoc.x] = START_LOC_VALUE; 

	m_posGoalLoc.x = m_nWidth - 2;
	m_posGoalLoc.y = m_nHeight - 2;
	m_ppMaze[m_posGoalLoc.y][m_posGoalLoc.x] = PASS_VALUE;
}

MyObjects::Maze::~Maze()
{
	for (int row = 0; row < m_nHeight; row++)
		delete[] m_ppMaze[row];
	delete[] m_ppMaze;
}

int MyObjects::Maze::GetWidth()
{
	return m_nWidth;
}

int MyObjects::Maze::GetHeight()
{
	return m_nHeight;
}

short MyObjects::Maze::GetValue(int row, int col)
{
	return m_ppMaze[row][col];
}

void MyObjects::Maze::SetValue(int row, int col, short value)
{
	m_ppMaze[row][col] = value;
}

CPoint MyObjects::Maze::GetStartLoc()
{
	return m_posStartLoc;
}

CPoint MyObjects::Maze::GetGoalLoc()
{
	return m_posGoalLoc;
}

short** MyObjects::Maze::GetMaze()
{
	return m_ppMaze;
}