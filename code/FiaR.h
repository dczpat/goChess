#pragma once
#include "gadgets.h"

class FIAR
{
private:
	Color board[9][9];//8*8的棋盘
	string timestamp;//开始时间
	int sum;//棋子总数
	Color ownColor, oppoColor;//本方、对方颜色
	bool complete(int x, int y);//判断此位置是否成功连线
	void refresh();//刷新屏幕
	void layout();//绘制棋盘
	void leave(int mode);//退出
public:
	int startGame();
	FIAR();
	FIAR(string ts);
	string getTS();
	~FIAR() = default;
};