#pragma once
#include "gadgets.h"
#include "Reversi.h"
#include "FiaR.h"
#include "Jumpy.h"

class Admin
{
private:
	//�洢����ģʽ���ԵĴ浵����
	vector<string> reversi;
	vector<string> fiar;
	vector<string> jumpy;
	void subMenu(int mode);//��һ���˵�
	void recordMenu(int mode);//��Ϸ��¼�˵�
	void storeRecords();//�����¼
public:
	void mainMenu();//���˵�
	Admin();
	~Admin() = default;
};