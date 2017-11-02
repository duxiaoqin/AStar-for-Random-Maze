/*
	Programmed by Xiaoqin Du, 383979583@qq.com
	School of Math and Computer Science, 
	Wuhan Textile University
*/

#pragma once

#include <deque>
#include <algorithm>

#include "Maze.h"

namespace MyAI {

	struct MazeNode { //迷宫节点的信息，用于A*搜索
		CPoint pos; //节点的位置
		int g; //实际代价
		int h; //估算代价
		int f; //总体代价
	};

	bool MazeNodeLessCompare(MazeNode* pNode1, MazeNode* pNode2); //在std::sort中，用于元素的比较
	bool PointEqualCompare(CPoint* pPos1, CPoint* pPos2);

	class SearchMaze {
	public:
		SearchMaze(MyObjects::Maze* pMaze);
		~SearchMaze();
		CPoint* GetPossibleMoves(CPoint pos); //从当前位置获取下一可达位置（排除障碍和已走位置）
		CPoint* GetAllPossibleMoves(CPoint pos); //从当前位置获取下一可达位置（仅仅排除障碍）
		void AStarSearch();
		CPoint* GetPathPoints(int* outCount);

	public:
		static const int UNSEARCH_VALUE = -1;

	private:
		MyObjects::Maze* m_pMaze;
		short** m_ppMaze;

		CPoint m_posStart;
		CPoint m_posGoal;
		CPoint m_posCurrent;

		CPoint** m_ppMazePoints;

		CPoint* m_pMazePathPoints;

		bool isFound;

		std::deque<MazeNode*> m_dequeAStarOpen; //A*的OPEN表，本类对象分配空间并负责回收
		std::deque<MazeNode*> m_dequeAStarClosed; //A*的CLOSED表，本类对象分配空间并负责回收
	};
}