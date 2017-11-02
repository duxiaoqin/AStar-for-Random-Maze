/*
	Programmed by Xiaoqin Du, 383979583@qq.com
	School of Math and Computer Science, 
	Wuhan Textile University
*/

#pragma once

namespace MyObjects {
	class Maze {
	public:
		Maze(int width, int height);
		~Maze();

		int GetWidth();
		int GetHeight();
		short GetValue(int row, int col);
		void SetValue(int row, int col, short value);
		CPoint GetStartLoc();
		CPoint GetGoalLoc();
		short** GetMaze();

	public:
		static const short PASS_VALUE = -1;
		static const short OBSTACLE_VALUE = -2;
		static const short START_LOC_VALUE = 0; // search depth for start = 0

		CPoint m_posStartLoc;
		CPoint m_posGoalLoc;

	private:
		int m_nWidth;
		int m_nHeight;

		short** m_ppMaze;
	};
}