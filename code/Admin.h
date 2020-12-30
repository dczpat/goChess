#pragma once
#include "gadgets.h"
#include "Reversi.h"
#include "FiaR.h"
#include "Jumpy.h"

class Admin
{
private:
	//存储三种模式各自的存档集合
	vector<string> reversi;
	vector<string> fiar;
	vector<string> jumpy;
	void subMenu(int mode);//次一级菜单
	void recordMenu(int mode);//游戏记录菜单
	void storeRecords();//保存记录
public:
	void mainMenu();//主菜单
	Admin();
	~Admin() = default;
};