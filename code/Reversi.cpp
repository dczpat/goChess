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
	else//该位置不合法
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
			cout << "本轮由黑方出子！";
		else
			cout << "本轮由白方出子！";
		//搜索下一步的合法落子位置，以不同颜色展示
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

		//无合法落子处
		if (!avl1)
		{
			//继续下一轮
			if (avl2)
			{
				avl2 = false;
				flag = false;
				ownColor = oppoColor;
				oppoColor = oppoColor == BLACK ? WHITE : BLACK;
				go_to(15, 5);
				cout << "本轮无法出子！";
				Sleep(3000);
				go_to(15, 5);
				cout << "                     ";
				continue;
			}
			//双方均无落子处，终止游戏
			else
				break;
		}

		whiteCnt = 0;
		blackCnt = 0;

		//玩家选择合法位置
		go_to(1, 10);
		cout << "请输入放置棋子的坐标（以空格分开）：";
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
			cout << "落子位置非法，请重新输入！";
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

		//取出与这个棋子有关系的落子 将夹在其中的对方棋子颜色转换
		for (auto& pos : attached[make_pair(x, y)])
		{
			switch (posCase(curPos, pos))
			{
				//列
			case 1:
				for (int j = min(curPos.y, pos.y) + 1;
					j < max(curPos.y, pos.y);
					++j)
				{
					board[curPos.x][j] = ownColor;
				}

				break;
				//行
			case 2:
				for (int i = min(curPos.x, pos.x) + 1;
					i < max(curPos.x, pos.x);
					++i)
				{
					board[i][curPos.y] = ownColor;
				}
				break;
				//对角线
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

		//统计双方棋子数量
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

		//刷新棋盘
		refresh();

		//棋盘已满或某方已无棋子 => 游戏终止		
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
	cout << "黑子数：" << blackCnt << " | 白子数：" << whiteCnt;
	go_to(15, 7);
	if (blackCnt > whiteCnt)
		cout << "黑方胜出！" << endl;
	else if (blackCnt < whiteCnt)
		cout << "白方胜出！" << endl;
	else
		cout << "平局！" << endl;
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

//查找某个点对应的可供选择的合法位置
bool Reversi::findAvl(int x, int y)
{
	//每次找到后用颜色标出来
	bool ret = false, changed = false;
	int i, j;
	//左
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
	//右
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
	//上
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
	//下
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
	//左上
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
	//左下
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
	//右上
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
	//右下
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
	//提示信息
	go_to(15, 2);
	cout << "提示：*->黑子   #->白子   @->当前合法棋步" << endl;
	go_to(15, 3);
	cout << "输入坐标(0,0)可直接退出，或(0,1)以存档..." << endl;
}

void Reversi::leave(int mode)
{
	ofstream outf;
	switch (mode)
	{
	case 0:

		go_to(15, 9);
		cout << "正在退出...";
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
		cout << "正在保存并退出...";
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



