#pragma once
#include "gadgets.h"

class FIAR
{
private:
	Color board[9][9];//8*8������
	string timestamp;//��ʼʱ��
	int sum;//��������
	Color ownColor, oppoColor;//�������Է���ɫ
	bool complete(int x, int y);//�жϴ�λ���Ƿ�ɹ�����
	void refresh();//ˢ����Ļ
	void layout();//��������
	void leave(int mode);//�˳�
public:
	int startGame();
	FIAR();
	FIAR(string ts);
	string getTS();
	~FIAR() = default;
};