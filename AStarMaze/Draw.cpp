/*
	Programmed by Xiaoqin Du, 383979583@qq.com
	School of Math and Computer Science, 
	Wuhan Textile University
*/

#include "stdafx.h"

#include "Draw.h"
#include "Maze.h"

MyGDI::Draw::Draw(MyObjects::Maze* pMaze)
{
	m_nGridWidth = 30;
	m_nGridHeight = 30;

	m_nXStart = 0;
	m_nYStart = 0;

	m_pMaze = pMaze;
}

MyGDI::Draw::~Draw()
{
}

void MyGDI::Draw::DrawMaze(CDC* pDC, CPoint* pPathPoints, int count)
{
	int row, col;
	int xStart = m_nXStart;
	int yStart = m_nYStart;

	int value;

	for (row = 0; row < m_pMaze->GetHeight(); row++) {
		for (col = 0; col < m_pMaze->GetWidth(); col++) {
			value = m_pMaze->GetValue(row, col);
			if ( value == m_pMaze->OBSTACLE_VALUE)
				DrawObstacle(pDC, xStart, yStart, xStart + m_nGridWidth, yStart + m_nGridHeight);
			else if (value != m_pMaze->OBSTACLE_VALUE) {
				DrawNormal(pDC, xStart, yStart, xStart + m_nGridWidth, yStart + m_nGridHeight);
				//if (value >= 0)
				//	DrawDepthText(pDC, xStart, yStart, xStart + m_nGridWidth, yStart + m_nGridHeight, value);
			}
			xStart += m_nGridWidth;
		}
		xStart = m_nXStart;
		yStart += m_nGridHeight;
	}

	if (!pPathPoints)
		return;
	for (int i = 0; i < count; i++) {
		row = pPathPoints[i].y; col = pPathPoints[i].x;
		value = m_pMaze->GetValue(row, col);
		xStart = m_nXStart + col * m_nGridWidth;
		yStart = m_nYStart + row * m_nGridHeight;
		DrawDepthText(pDC, xStart, yStart, xStart + m_nGridWidth, yStart + m_nGridHeight, value);
	}
}

void MyGDI::Draw::DrawObstacle(CDC* pDC, int x1, int y1, int x2, int y2)
{
	CBrush brushBlue(RGB(0, 0, 255));
	CBrush* pOldBrush = pDC->SelectObject(&brushBlue);
				
	CPen penBlack;
	penBlack.CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	CPen* pOldPen = pDC->SelectObject(&penBlack);

	pDC->Rectangle(x1, y1, x2, y2);

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}

void MyGDI::Draw::DrawNormal(CDC* pDC, int x1, int y1, int x2, int y2)
{
	CBrush brushBlue(RGB(0, 255, 0));
	CBrush* pOldBrush = pDC->SelectObject(&brushBlue);
				
	CPen penBlack;
	penBlack.CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	CPen* pOldPen = pDC->SelectObject(&penBlack);

	pDC->Rectangle(x1, y1, x2, y2);

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}

void MyGDI::Draw::DrawDepthText(CDC* pDC, int x1, int y1, int x2, int y2, int depth)
{
	CString str;
	str.Format(L"%d", depth);
	pDC->TextOut(x1, y1,str);
}