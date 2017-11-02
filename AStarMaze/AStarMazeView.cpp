/*
	Programmed by Xiaoqin Du, 383979583@qq.com
	School of Math and Computer Science, 
	Wuhan Textile University
*/

// AStarMazeView.cpp : implementation of the CAStarMazeView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "AStarMaze.h"
#endif

#include "AStarMazeDoc.h"
#include "AStarMazeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAStarMazeView

IMPLEMENT_DYNCREATE(CAStarMazeView, CView)

BEGIN_MESSAGE_MAP(CAStarMazeView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CAStarMazeView construction/destruction

CAStarMazeView::CAStarMazeView()
{
	// TODO: add construction code here
	m_pMaze = new MyObjects::Maze(30, 20);
	m_pSearch = new MyAI::SearchMaze(m_pMaze);
	m_pSearch->AStarSearch();
	m_pPathPoints = m_pSearch->GetPathPoints(&m_nCount);
	m_pDraw = new MyGDI::Draw(m_pMaze);
}

CAStarMazeView::~CAStarMazeView()
{
	delete[] m_pPathPoints;
	delete m_pDraw;
	delete m_pSearch;
	delete m_pMaze;
}

BOOL CAStarMazeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CAStarMazeView drawing

void CAStarMazeView::OnDraw(CDC* pDC)
{
	CAStarMazeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	m_pDraw->DrawMaze(pDC, m_pPathPoints, m_nCount);
}


// CAStarMazeView printing

BOOL CAStarMazeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CAStarMazeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CAStarMazeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CAStarMazeView diagnostics

#ifdef _DEBUG
void CAStarMazeView::AssertValid() const
{
	CView::AssertValid();
}

void CAStarMazeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAStarMazeDoc* CAStarMazeView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAStarMazeDoc)));
	return (CAStarMazeDoc*)m_pDocument;
}
#endif //_DEBUG


// CAStarMazeView message handlers
