/*
	Programmed by Xiaoqin Du, 383979583@qq.com
	School of Math and Computer Science, 
	Wuhan Textile University
*/

// AStarMazeView.h : interface of the CAStarMazeView class
//

#pragma once

#include "Maze.h"
#include "Search.h"
#include "Draw.h"

class CAStarMazeView : public CView
{
protected: // create from serialization only
	CAStarMazeView();
	DECLARE_DYNCREATE(CAStarMazeView)

// Attributes
public:
	CAStarMazeDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CAStarMazeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

private:
	MyObjects::Maze* m_pMaze;
	MyAI::SearchMaze* m_pSearch;
	CPoint* m_pPathPoints;
	int m_nCount;
	MyGDI::Draw* m_pDraw;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in AStarMazeView.cpp
inline CAStarMazeDoc* CAStarMazeView::GetDocument() const
   { return reinterpret_cast<CAStarMazeDoc*>(m_pDocument); }
#endif

