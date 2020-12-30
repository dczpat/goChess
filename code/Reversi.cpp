#include "Reversi.h"
void go_to(int x, int y);

Reversi::Reversi()
{
	time_t now = time(0);
	timestamp = ctime(&now);
	timestamp.erase(timestamp.end() - 1);
	replace(timestamp.begin(), timestamp.end(), ':', '-');
	ownColor = BLACK;
	oppoColor = WHITE;
	avl2 = true;
	for (int i = 1; i <= 8; ++i)
	{
		for (int j = 1; j <= 8; ++j)
			board[i][j] = EMPTY;
	}
	board[4][4] = BLACK;
	board[4][5] = WHITE;
	board[5][4] = WHITE;
	board[5][5] = BLACK;
	cnt = 4;
}

Reversi::Reversi(string ts)
{
	timestamp = ts;
	avl2 = true;
	cnt = 0;
	ifstream inf;
	inf.open("docs/Reversi/" + ts + ".txt", ios::in);
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
				cnt++;
		}
	}
	inf.close();
}


int posCase(Position& m, Position& n)
{
	if (m.x == n.x)
		return 1;
	else if (m.y == n.y)
		return 2;
	else if (abs(m.x - n.x) == abs(m.y - n.y))
		return 3;
	else//��λ�ò��Ϸ�
		return 0;
}


int Reversi::startGame()
{
	int x = 0, y = 0; //input
	bool flag = false;
	//paint layout
	layout();
	refresh();
	while (true)
	{
		go_to(15, 4);
		if (ownColor == BLACK)
			cout << "�����ɺڷ����ӣ�";
		else
			cout << "�����ɰ׷����ӣ�";
		//������һ���ĺϷ�����λ�ã��Բ�ͬ��ɫչʾ
		for (int i = 1; i <= 8; ++i)
		{
			for (int j = 1; j <= 8; ++j)
			{
				if (board[i][j] == ownColor)
				{
					flag = findAvl(i, j);
					if (flag)
					{
						avl1 = true;
					}
				}
			}
		}

		//�޺Ϸ����Ӵ�
		if (!avl1)
		{
			//������һ��
			if (avl2)
			{
				avl2 = false;
				flag = false;
				ownColor = oppoColor;
				oppoColor = oppoColor == BLACK ? WHITE : BLACK;
				go_to(15, 5);
				cout << "�����޷����ӣ�";
				Sleep(3000);
				go_to(15, 5);
				cout << "                     ";
				continue;
			}
			//˫���������Ӵ�����ֹ��Ϸ
			else
				break;
		}

		whiteCnt = 0;
		blackCnt = 0;

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

		while (attached.find(make_pair(x, y)) == attached.end())
		{
			if (x == 0 && (y == 0 || y == 1))
			{
				leave(y);
				return y;
			}
			go_to(10, 10);
			cout << "                         ";
			go_to(1, 11);
			cout << "����λ�÷Ƿ������������룡";
			go_to(10, 10);
			cin >> x >> y;
		}
		go_to(10, 10);
		cout << "                            ";
		go_to(1, 11);
		cout << "                            ";
		curPos = Position(x, y);
		board[x][y] = ownColor;
		cnt++;

		//ȡ������������й�ϵ������ ���������еĶԷ�������ɫת��
		for (auto& pos : attached[make_pair(x, y)])
		{
			switch (posCase(curPos, pos))
			{
				//��
			case 1:
				for (int j = min(curPos.y, pos.y) + 1;
					j < max(curPos.y, pos.y);
					++j)
				{
					board[curPos.x][j] = ownColor;
				}

				break;
				//��
			case 2:
				for (int i = min(curPos.x, pos.x) + 1;
					i < max(curPos.x, pos.x);
					++i)
				{
					board[i][curPos.y] = ownColor;
				}
				break;
				//�Խ���
			case 3:
				if (curPos.x < pos.x && curPos.y < pos.y)
				{
					for (int i = curPos.x + 1, j = curPos.y + 1;
						i < pos.x, j < pos.y;
						++i, ++j)
					{
						board[i][j] = ownColor;
					}

				}
				else if (curPos.x > pos.x && curPos.y > pos.y)
				{
					for (int i = pos.x + 1, j = pos.y + 1;
						i < curPos.x, j < curPos.y;
						++i, ++j)
					{
						board[i][j] = ownColor;
					}
				}
				else if (curPos.x < pos.x && curPos.y > pos.y)
				{
					for (int i = curPos.x + 1, j = curPos.y - 1;
						i < pos.x, j > pos.y;
						++i, --j)
					{
						board[i][j] = ownColor;
					}
				}
				else
				{
					for (int i = pos.x + 1, j = pos.y - 1;
						i < curPos.x, j > curPos.y;
						++i, --j)
					{
						board[i][j] = ownColor;
					}
				}
				break;
			default:
				break;
			}
		}

		//ͳ��˫����������
		for (int i = 1; i <= 8; ++i)
		{
			for (int j = 1; j <= 8; ++j)
			{
				if (board[i][j] == WHITE)
				{
					whiteCnt++;
				}
				else if (board[i][j] == BLACK)
				{
					blackCnt++;
				}
			}
		}

		//ˢ������
		refresh();

		//����������ĳ���������� => ��Ϸ��ֹ		
		if (cnt == 64 || blackCnt == 0 || whiteCnt == 0)
			break;

		flag = false;
		avl1 = false;
		avl2 = true;
		//switch color 
		ownColor = oppoColor;
		oppoColor = oppoColor == BLACK ? WHITE : BLACK;
		/*whiteCnt = 0;
		blackCnt = 0;*/
		attached.clear();

	}

	go_to(15, 6);
	cout << "��������" << blackCnt << " | ��������" << whiteCnt;
	go_to(15, 7);
	if (blackCnt > whiteCnt)
		cout << "�ڷ�ʤ����" << endl;
	else if (blackCnt < whiteCnt)
		cout << "�׷�ʤ����" << endl;
	else
		cout << "ƽ�֣�" << endl;
	Sleep(3500);
	return 0;
}

void Reversi::refresh()
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
			else
			{
				go_to(i, j);
				cout << ' ';
			}
		}
	}
}

//����ĳ�����Ӧ�Ŀɹ�ѡ��ĺϷ�λ��
bool Reversi::findAvl(int x, int y)
{
	//ÿ���ҵ�������ɫ�����
	bool ret = false, changed = false;
	int i, j;
	//��
	i = x - 1;
	j = y;
	while (i >= 1 && board[i][j] == oppoColor)
	{
		changed = true;
		i--;
	}
	if (changed && i >= 1 && board[i][j] == EMPTY)
	{
		attached[make_pair(i, j)].push_back(Position(x, y));
		ret = true;
		go_to(i, j);
		cout << '@' << endl;
	}
	//��
	changed = false;
	i = x + 1;
	j = y;
	while (i <= 8 && board[i][j] == oppoColor)
	{
		changed = true;
		i++;
	}
	if (changed && i <= 8 && board[i][j] == EMPTY)
	{
		attached[make_pair(i, j)].push_back(Position(x, y));
		ret = true;
		go_to(i, j);
		cout << '@' << endl;
	}
	//��
	changed = false;
	i = x;
	j = y + 1;
	while (j <= 8 && board[i][j] == oppoColor)
	{
		changed = true;
		j++;
	}
	if (changed && j <= 8 && board[i][j] == EMPTY)
	{
		attached[make_pair(i, j)].push_back(Position(x, y));
		ret = true;
		go_to(i, j);
		cout << '@' << endl;
	}
	//��
	changed = false;
	i = x;
	j = y - 1;
	while (j >= 1 && board[i][j] == oppoColor)
	{
		changed = true;
		j--;
	}
	if (changed && j >= 1 && board[i][j] == EMPTY)
	{
		attached[make_pair(i, j)].push_back(Position(x, y));
		ret = true;
		go_to(i, j);
		cout << '@' << endl;
	}
	//����
	changed = false;
	i = x - 1;
	j = y + 1;
	while (i >= 1 && j <= 8 && board[i][j] == oppoColor)
	{
		changed = true;
		i--;
		j++;
	}
	if (changed && i >= 1 && j <= 8 && board[i][j] == EMPTY)
	{
		attached[make_pair(i, j)].push_back(Position(x, y));
		ret = true;
		go_to(i, j);
		cout << '@' << endl;
	}
	//����
	changed = false;
	i = x - 1;
	j = y - 1;
	while (i >= 1 && j >= 1 && board[i][j] == oppoColor)
	{
		changed = true;
		i--;
		j--;
	}
	if (changed && i >= 1 && j >= 1 && board[i][j] == EMPTY)
	{
		attached[make_pair(i, j)].push_back(Position(x, y));
		ret = true;
		go_to(i, j);
		cout << '@' << endl;
	}
	//����
	changed = false;
	i = x + 1;
	j = y + 1;
	while (i <= 8 && j <= 8 && board[i][j] == oppoColor)
	{
		changed = true;
		i++;
		j++;
	}
	if (changed && i <= 8 && j <= 8 && board[i][j] == EMPTY)
	{
		attached[make_pair(i, j)].push_back(Position(x, y));
		ret = true;
		go_to(i, j);
		cout << '@' << endl;
	}
	//����
	changed = false;
	i = x + 1;
	j = y - 1;
	while (i <= 8 && j >= 1 && board[i][j] == oppoColor)
	{
		changed = true;
		i++;
		j--;
	}
	if (changed && i <= 8 && j >= 1 && board[i][j] == EMPTY)
	{
		attached[make_pair(i, j)].push_back(Position(x, y));
		ret = true;
		go_to(i, j);
		cout << '@' << endl;
	}
	return ret;
}

void Reversi::layout()
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
	go_to(4, 4);
	cout << '*';
	go_to(5, 5);
	cout << '*';
	go_to(4, 5);
	cout << '#';
	go_to(5, 4);
	cout << '#';
	//��ʾ��Ϣ
	go_to(15, 2);
	cout << "��ʾ��*->����   #->����   @->��ǰ�Ϸ��岽" << endl;
	go_to(15, 3);
	cout << "��������(0,0)��ֱ���˳�����(0,1)�Դ浵..." << endl;
}

void Reversi::leave(int mode)
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
		outf.open("docs/Reversi/" + timestamp + ".txt", ios::out | ios::trunc);
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

string Reversi::getTS()
{
	return timestamp;
}



