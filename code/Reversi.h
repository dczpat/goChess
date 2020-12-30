#pragma once
#include "gadgets.h"

class Reversi
{
private:
	Color board[9][9];//8*8������
	string timestamp;//��ʼʱ��
	//bool avlWhite[8][8];
	//bool avlBlack[8][8];
	bool avl1, avl2;//��ǰ��ǰһ���Ƿ��кϷ�λ�ü�������
	int cnt;//�������� ��ֵΪ4
	int blackCnt, whiteCnt;//���ӡ����ӵļ���
	map<pair<int, int>, vector<Position>> attached;//������λ��->��Ӧ�ı���λ��
	Position curPos;
	Color ownColor, oppoColor;//�������Է���ɫ
	bool findAvl(int x, int y);//���ҵ�ǰλ���Ƿ���ڶ�Ӧ�Ŀ�����λ��
	void refresh();//ˢ����Ļ
	void layout();//��������
	void leave(int mode);//�뿪��Ϸ
public:
	Reversi();
	Reversi(string ts);
	string getTS();
	~Reversi() = default;
	int startGame();
};