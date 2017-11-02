/*
	Programmed by Xiaoqin Du, 383979583@qq.com
	School of Math and Computer Science, 
	Wuhan Textile University
*/

#pragma once

#include "Maze.h"

namespace MyGDI {
	class Draw{
	public:
		Draw(MyObjects::Maze* pMaze);
		~Draw();

		void DrawMaze(CDC* pDC, CPoint* pPathPoints, int count);

	private:
		void DrawObstacle(CDC* pDC, int x1, int y1, int x2, int y2);
		void DrawNormal(CDC* pDC, int x1, int y1, int x2, int y2);
		void DrawDepthText(CDC* pDC, int x1, int y1, int x2, int y2, int depth);

	private:
		MyObjects::Maze* m_pMaze;

		int m_nGridWidth;
		int m_nGridHeight;

		int m_nXStart;
		int m_nYStart;
	};
}