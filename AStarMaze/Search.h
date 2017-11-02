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

	struct MazeNode { //�Թ��ڵ����Ϣ������A*����
		CPoint pos; //�ڵ��λ��
		int g; //ʵ�ʴ���
		int h; //�������
		int f; //�������
	};

	bool MazeNodeLessCompare(MazeNode* pNode1, MazeNode* pNode2); //��std::sort�У�����Ԫ�صıȽ�
	bool PointEqualCompare(CPoint* pPos1, CPoint* pPos2);

	class SearchMaze {
	public:
		SearchMaze(MyObjects::Maze* pMaze);
		~SearchMaze();
		CPoint* GetPossibleMoves(CPoint pos); //�ӵ�ǰλ�û�ȡ��һ�ɴ�λ�ã��ų��ϰ�������λ�ã�
		CPoint* GetAllPossibleMoves(CPoint pos); //�ӵ�ǰλ�û�ȡ��һ�ɴ�λ�ã������ų��ϰ���
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

		std::deque<MazeNode*> m_dequeAStarOpen; //A*��OPEN������������ռ䲢�������
		std::deque<MazeNode*> m_dequeAStarClosed; //A*��CLOSED������������ռ䲢�������
	};
}