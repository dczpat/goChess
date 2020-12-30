#pragma once
#include "gadgets.h"

class Reversi
{
private:
	Color board[9][9];//8*8的棋盘
	string timestamp;//开始时间
	//bool avlWhite[8][8];
	//bool avlBlack[8][8];
	bool avl1, avl2;//当前、前一次是否有合法位置继续下子
	int cnt;//棋子总数 初值为4
	int blackCnt, whiteCnt;//黑子、白子的计数
	map<pair<int, int>, vector<Position>> attached;//可落子位置->对应的本方位置
	Position curPos;
	Color ownColor, oppoColor;//本方、对方颜色
	bool findAvl(int x, int y);//查找当前位置是否存在对应的可落子位置
	void refresh();//刷新屏幕
	void layout();//绘制棋盘
	void leave(int mode);//离开游戏
public:
	Reversi();
	Reversi(string ts);
	string getTS();
	~Reversi() = default;
	int startGame();
};