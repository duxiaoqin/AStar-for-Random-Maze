/*
	Programmed by Xiaoqin Du, 383979583@qq.com
	School of Math and Computer Science, 
	Wuhan Textile University
*/

#include "stdafx.h"

#include "Search.h"

MyAI::SearchMaze::SearchMaze(MyObjects::Maze* pMaze)
{
	m_pMaze = pMaze;
	m_ppMaze = m_pMaze->GetMaze();
	m_posStart = m_pMaze->GetStartLoc();
	m_posGoal = m_pMaze->GetGoalLoc();
	m_posCurrent = m_posStart;
	m_pMazePathPoints = NULL;

	//将开始节点加入A*的OPEN表
	MazeNode* pNode = new MazeNode();
	pNode->pos = m_posStart;
	m_dequeAStarOpen.push_front(pNode);

	isFound = false;

	m_ppMazePoints = new CPoint*[m_pMaze->GetHeight()];
	for (int row = 0; row < m_pMaze->GetHeight(); row++)
		m_ppMazePoints[row] = new CPoint[m_pMaze->GetWidth()];

	for (int row = 0; row < m_pMaze->GetHeight(); row++)
		for (int col = 0; col < m_pMaze->GetWidth(); col++) {
			m_ppMazePoints[row][col].x = UNSEARCH_VALUE;
			m_ppMazePoints[row][col].y = UNSEARCH_VALUE;
		}
}

MyAI::SearchMaze::~SearchMaze()
{
	//回收m_ppMazePoints空间
	for (int row = 0; row < m_pMaze->GetHeight(); row++)
		delete[] m_ppMazePoints[row];
	delete[] m_ppMazePoints;

	//回收A*的OPEN表空间
	std::deque<MazeNode*>::iterator iterA;
	iterA = m_dequeAStarOpen.begin();
	while (iterA != m_dequeAStarOpen.end()) {
		delete *iterA;
		iterA++;
	}
	m_dequeAStarOpen.clear();

	//回收A*的CLOSED表空间
	iterA = m_dequeAStarClosed.begin();
	while (iterA != m_dequeAStarClosed.end()) {
		delete *iterA;
		iterA++;
	}
	m_dequeAStarClosed.clear();
}

CPoint* MyAI::SearchMaze::GetPossibleMoves(CPoint pos)
{
	CPoint* possMoves = new CPoint[4];
	for (int i = 0; i < 4; i++) {
		possMoves[i].x = UNSEARCH_VALUE;
		possMoves[i].y = UNSEARCH_VALUE;
	}

	if (m_ppMaze[pos.y][pos.x-1] == m_pMaze->PASS_VALUE) {
		possMoves[0].x = pos.x - 1;
		possMoves[0].y = pos.y;
	}

	if (m_ppMaze[pos.y][pos.x+1] == m_pMaze->PASS_VALUE) {
		possMoves[1].x = pos.x + 1;
		possMoves[1].y = pos.y;
	}

	if (m_ppMaze[pos.y-1][pos.x] == m_pMaze->PASS_VALUE) {
		possMoves[2].x = pos.x;
		possMoves[2].y = pos.y - 1;
	}

	if (m_ppMaze[pos.y+1][pos.x] == m_pMaze->PASS_VALUE) {
		possMoves[3].x = pos.x;
		possMoves[3].y = pos.y + 1;
	}

	return possMoves;
}

CPoint* MyAI::SearchMaze::GetAllPossibleMoves(CPoint pos)
{
	CPoint* possMoves = new CPoint[4];
	for (int i = 0; i < 4; i++) {
		possMoves[i].x = UNSEARCH_VALUE;
		possMoves[i].y = UNSEARCH_VALUE;
	}

	if (m_ppMaze[pos.y][pos.x-1] != m_pMaze->OBSTACLE_VALUE) {
		possMoves[0].x = pos.x - 1;
		possMoves[0].y = pos.y;
	}

	if (m_ppMaze[pos.y][pos.x+1] != m_pMaze->OBSTACLE_VALUE) {
		possMoves[1].x = pos.x + 1;
		possMoves[1].y = pos.y;
	}

	if (m_ppMaze[pos.y-1][pos.x] != m_pMaze->OBSTACLE_VALUE) {
		possMoves[2].x = pos.x;
		possMoves[2].y = pos.y - 1;
	}

	if (m_ppMaze[pos.y+1][pos.x] != m_pMaze->OBSTACLE_VALUE) {
		possMoves[3].x = pos.x;
		possMoves[3].y = pos.y + 1;
	}

	return possMoves;
}

void MyAI::SearchMaze::AStarSearch()
{
	MazeNode* pNode;

	isFound = false;
	while (!m_dequeAStarOpen.empty() && !isFound) {
		pNode = m_dequeAStarOpen.front();
		m_dequeAStarOpen.pop_front();
		m_dequeAStarClosed.push_back(pNode);

		if (pNode->pos.y == m_posGoal.y &&
			pNode->pos.x == m_posGoal.x) {
			isFound = true;
		}
		else {
			CPoint* moves = GetAllPossibleMoves(pNode->pos); //获取所有可能的下一位置（仅仅排除障碍物）：包括已访问位置
			short depth = m_ppMaze[pNode->pos.y][pNode->pos.x];

			for (int i = 0; i < 4; i++) {
				if (moves[i].x == UNSEARCH_VALUE ||
					moves[i].y == UNSEARCH_VALUE)
					continue; //障碍物
				
				if (m_ppMaze[moves[i].y][moves[i].x] == m_pMaze->PASS_VALUE) {//首次访问
					m_ppMaze[moves[i].y][moves[i].x] = depth + 1;
					m_ppMazePoints[moves[i].y][moves[i].x] = pNode->pos;
					MazeNode* pNodeTmp = new MazeNode();
					pNodeTmp->pos = moves[i];
					pNodeTmp->g = depth + 1;
					pNodeTmp->h = abs(m_posGoal.y - moves[i].y) + abs(m_posGoal.x - moves[i].x);
					pNodeTmp->f = pNodeTmp->g + pNodeTmp->h;

					m_dequeAStarOpen.push_front(pNodeTmp);
					std::sort(m_dequeAStarOpen.begin(), m_dequeAStarOpen.end(), MazeNodeLessCompare);
				}
				else if (m_ppMaze[moves[i].y][moves[i].x] > depth + 1) {//以前访问过，但路径不是最优
					CPoint pos(moves[i].x, moves[i].y);
					//pos.y = moves[i].y; pos.x = moves[i].x;
					std::deque<MazeNode*>::iterator iterA;
					iterA = m_dequeAStarOpen.begin();
					while (iterA != m_dequeAStarOpen.end()) {
						if (PointEqualCompare(&(*iterA)->pos, &pos)) {//从OPEN表中找到该节点，删除掉；如果没有找到，说明已经在CLOSED表中，重新加入OPEN表即可
							m_dequeAStarClosed.push_back(*iterA); //放入CLOSED表，回收空间用
							m_dequeAStarOpen.erase(iterA);
							break;
						}
						iterA++;
					}

					//更新信息，重新加入OPEN表
					m_ppMaze[moves[i].y][moves[i].x] = depth + 1;
					m_ppMazePoints[moves[i].y][moves[i].x] = pNode->pos;
					MazeNode* pNodeTmp = new MazeNode();
					pNodeTmp->pos = moves[i];
					pNodeTmp->g = depth + 1;
					pNodeTmp->h = abs(m_posGoal.y - moves[i].y) + abs(m_posGoal.x - moves[i].x);
					pNodeTmp->f = pNodeTmp->g + pNodeTmp->h;

					m_dequeAStarOpen.push_front(pNodeTmp);
					std::sort(m_dequeAStarOpen.begin(), m_dequeAStarOpen.end(), MazeNodeLessCompare);
				}
				//m_dequeAStarOpen.insert(std::lower_bound(m_dequeAStarOpen.begin(), m_dequeAStarOpen.end(), pNodeTmp), pNodeTmp); //按pNodeTmp->f由小到大排列

				if (moves[i].y == m_posGoal.y &&
					moves[i].x == m_posGoal.x) {
					isFound = true;
				}
			}
			delete moves;
		}
	}
}

bool MyAI::MazeNodeLessCompare(MazeNode* pNode1, MazeNode* pNode2)
{
	return pNode1->f < pNode2->f;
}

bool MyAI::PointEqualCompare(CPoint* pPos1, CPoint* pPos2)
{
	return pPos1->y == pPos2->y && pPos1->x == pPos2->x;
}

CPoint* MyAI::SearchMaze::GetPathPoints(int* outCount)
{
	bool isPath;
	int count;

	CPoint goalPos;
	CPoint curPos;

	isPath = false;
	count = 1;
	goalPos = m_pMaze->GetGoalLoc();
	curPos = m_ppMazePoints[goalPos.y][goalPos.x];

	while (curPos.x != UNSEARCH_VALUE && curPos.y != UNSEARCH_VALUE) {
		count++;
		if (curPos.y == m_pMaze->GetStartLoc().y && curPos.x == m_pMaze->GetStartLoc().x) {
			isPath = true;
			break;
		}
		curPos = m_ppMazePoints[curPos.y][curPos.x];
	}

	if (isPath) {
		*outCount = count;
		m_pMazePathPoints = new CPoint[count];
		isPath = false;
		count = 1;
		goalPos = m_pMaze->GetGoalLoc();
		curPos = m_ppMazePoints[goalPos.y][goalPos.x];
		m_pMazePathPoints[count-1] = goalPos;

		while (curPos.x != UNSEARCH_VALUE && curPos.y != UNSEARCH_VALUE) {
			count++;
			m_pMazePathPoints[count-1] = curPos;
			if (curPos.y == m_pMaze->GetStartLoc().y && curPos.x == m_pMaze->GetStartLoc().x) {
				isPath = true;
				break;
			}
			curPos = m_ppMazePoints[curPos.y][curPos.x];
		}
	}
	else
		m_pMazePathPoints = NULL;

	return m_pMazePathPoints;
}