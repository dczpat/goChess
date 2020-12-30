#pragma once
#include "gadgets.h"

//自创“跳棋”，类似五子棋，但须至少3个棋子间隔相连
class Jumpy
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
	Jumpy();
	Jumpy(string ts);
	string getTS();
	~Jumpy() = default;
};