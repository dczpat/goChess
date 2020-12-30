#include "Jumpy.h"

Jumpy::Jumpy()
{
	time_t now = time(0);
	timestamp = ctime(&now);
	timestamp.erase(timestamp.end() - 1);
	replace(timestamp.begin(), timestamp.end(), ':', '-');

	for (int i = 1; i <= 8; ++i)
	{
		for (int j = 1; j <= 8; ++j)
			board[i][j] = EMPTY;
	}
	sum = 0;
	ownColor = BLACK;
	oppoColor = WHITE;
}

Jumpy::Jumpy(string ts)
{
	timestamp = ts;
	sum = 0;
	ifstream inf;
	inf.open("docs/Jumpy/" + ts + ".txt", ios::in);
	int input;
	inf >> input;
	if (input == 0)
	{
		ownColor = BLACK;
		oppoColor = WHITE;
	}
	else
	{
		ownColor = WHITE;
		oppoColor = BLACK;
	}
	for (int i = 1; i <= 8; ++i)
	{
		for (int j = 1; j <= 8; ++j)
		{
			inf >> input;
			board[i][j] = Color(input);
			if (input != 2)
				sum++;
		}
	}
	inf.close();
}

void Jumpy::leave(int mode)
{
	ofstream outf;
	switch (mode)
	{
	case 0:
		go_to(15, 9);
		cout << "�����˳�...";
		Sleep(1200);
		break;
	case 1:
		outf.open("docs/Jumpy/" + timestamp + ".txt", ios::out | ios::trunc);
		if (ownColor == BLACK)
			outf << 0 << endl;
		else
			outf << 1 << endl;
		for (int i = 1; i <= 8; ++i)
		{
			for (int j = 1; j <= 8; ++j)
			{
				switch (board[i][j])
				{
				case 0:
					outf << 0 << ' ';
					break;
				case 1:
					outf << 1 << ' ';
					break;
				default:
					outf << 2 << ' ';
					break;
				}
			}
			outf << endl;
		}
		outf.close();
		go_to(15, 9);
		cout << "���ڱ��沢�˳�...";
		Sleep(1200);
		break;
	default:
		break;
	}
}


void Jumpy::layout()
{
	system("cls");
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(hOut, &CursorInfo);
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(hOut, &CursorInfo);

	cout << "    1   2   3   4   5   6   7   8" << endl;
	cout << "  |---|---|---|---|---|---|---|---|" << endl;
	for (int i = 1; i <= 8; ++i)
	{
		cout << i << " |   |   |   |   |   |   |   |   |" << endl;
		cout << "  |---|---|---|---|---|---|---|---|" << endl;
	}
	//��ʾ��Ϣ
	go_to(15, 2);
	cout << "��ʾ��*->����   #->����" << endl;
	go_to(15, 3);
	cout << "��������(0,0)��ֱ���˳�����(0,1)�Դ浵..." << endl;
}

void Jumpy::refresh()
{
	for (int i = 1; i <= 8; ++i)
	{
		for (int j = 1; j <= 8; ++j)
		{
			if (board[i][j] == WHITE)
			{
				go_to(i, j);
				cout << '#';
			}
			else if (board[i][j] == BLACK)
			{
				go_to(i, j);
				cout << '*';
			}
			//else
			//{
			//	go_to(i, j);
			//	cout << ' ';
			//}
		}
	}
}

bool Jumpy::complete(int x, int y)
{
	int m, n;
	int cnt;
	//��ֱ
	cnt = 0;
	m = y - 2;
	while (m >= 1 && m <= 8 && board[x][m] == ownColor)
	{
		cnt++;
		m -= 2;
	}
	m = y + 2;
	while (m >= 1 && m <= 8 && board[x][m] == ownColor)
	{
		cnt++;
		m += 2;
	}
	if (cnt >= 2)
		return true;
	//ˮƽ
	cnt = 0;
	n = x - 2;
	while (n >= 1 && n <= 8 && board[n][y] == ownColor)
	{
		cnt++;
		n -= 2;
	}
	n = x + 2;
	while (n >= 1 && n <= 8 && board[n][y] == ownColor)
	{
		cnt++;
		n += 2;
	}
	if (cnt >= 2)
		return true;
	//�Խ���
	cnt = 0;
	m = y - 2, n = x - 2;
	while (m >= 1 && m <= 8 && n >= 1 && n <= 8 && board[n][m] == ownColor)
	{
		cnt++;
		m -= 2;
		n -= 2;
	}
	m = y + 2, n = x + 2;
	while (m >= 1 && m <= 8 && n >= 1 && n <= 8 && board[n][m] == ownColor)
	{
		cnt++;
		m += 2;
		n += 2;
	}
	if (cnt >= 2)
		return true;

	cnt = 0;
	m = y - 2, n = x + 2;
	while (m >= 1 && m <= 8 && n >= 1 && n <= 8 && board[n][m] == ownColor)
	{
		cnt++;
		m -= 2;
		n += 2;
	}
	m = y + 2, n = x - 2;
	while (m >= 1 && m <= 8 && n >= 1 && n <= 8 && board[n][m] == ownColor)
	{
		cnt++;
		m += 2;
		n -= 2;
	}
	if (cnt >= 2)
		return true;
	return false;
}

int Jumpy::startGame()
{
	layout();
	refresh();
	int x, y;//input

	while (true)
	{
		go_to(15, 4);
		if (ownColor == BLACK)
			cout << "�����ɺڷ����ӣ�";
		else
			cout << "�����ɰ׷����ӣ�";

		//���ѡ��Ϸ�λ��
		go_to(1, 10);
		cout << "������������ӵ����꣨�Կո�ֿ�����";

		go_to(10, 10);
		cin >> x >> y;
		if (x == 0 && (y == 0 || y == 1))
		{
			leave(y);
			return y;
		}
		while (x < 1 || x > 8 || y < 1 || y > 8 || board[x][y] != EMPTY)
		{
			if (x == 0 && (y == 0 || y == 1))
			{
				leave(y);
				return y;
			}
			go_to(10, 10);
			cout << "                          ";
			go_to(1, 11);
			cout << "����λ�÷Ƿ������������룡";
			go_to(10, 10);
			cin >> x >> y;
		}
		go_to(10, 10);
		cout << "                              ";
		go_to(1, 11);
		cout << "                              ";
		board[x][y] = ownColor;
		refresh();
		if (complete(x, y))
		{
			go_to(2, 11);
			if (ownColor == BLACK)
				cout << "�ڷ�ʤ����";
			else
				cout << "�׷�ʤ����";
			Sleep(2000);
			return 0;
		}
		//switch color 
		ownColor = oppoColor;
		oppoColor = oppoColor == BLACK ? WHITE : BLACK;
		sum++;
		if (sum == 64)
		{
			cout << "����������";
			Sleep(2000);
			return 0;
		}
	}
}

string Jumpy::getTS()
{
	return timestamp;
}
