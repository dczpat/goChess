#include "Admin.h"

Admin::Admin()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(hOut, &CursorInfo);
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(hOut, &CursorInfo);

	ifstream inf;
	string input;

	inf.open("docs/Reversi.txt", ios::in);
	while (!inf.fail())
	{
		input = "";
		getline(inf, input);
		if (!input.empty())
			reversi.push_back(input);
	}
	inf.close();

	inf.open("docs/FiaR.txt", ios::in);
	while (!inf.fail())
	{
		input = "";
		getline(inf, input);
		if (!input.empty())
			fiar.push_back(input);
	}
	inf.close();

	inf.open("docs/Jumpy.txt", ios::in);
	while (!inf.fail())
	{
		input = "";
		getline(inf, input);
		if (!input.empty())
			jumpy.push_back(input);
	}
	inf.close();

}

void Admin::mainMenu()
{
	system("cls");
	int input;

	cout << "��ѡ�����Ĳ�����ţ�" << endl << endl
		<< "1. ��ת��" << endl
		<< "2. ������" << endl
		<< "3. ���ơ����塱" << endl
		<< "4. �˳���Ϸ" << endl << endl;
	cin >> input;
	switch (input)
	{
	case 1:
	case 2:
	case 3:
		subMenu(input);
		break;
	case 4:
		storeRecords();
		cout << endl << endl << "�����˳���Ϸ..." << endl;
		Sleep(1600);
		exit(0);
	default:
		cout << endl << endl << "����������..." << endl;
		Sleep(1600);
		mainMenu();
	}
}

void Admin::subMenu(int mode)
{
	system("cls");
	int input;

	cout << "��ѡ�����Ĳ�����ţ�" << endl << endl
		<< "1. ����Ϸ" << endl
		<< "2. ������Ϸ" << endl
		<< "3. �������˵�" << endl << endl;
	cin >> input;
	switch (input)
	{
	case 1:
		switch (mode)
		{
		case 1://Reversi
		{
			Reversi r;
			if (r.startGame())
				reversi.push_back(r.getTS());
			break;
		}
		case 2://FiaR
		{
			FIAR f;
			if (f.startGame())
				fiar.push_back(f.getTS());
			break;
		}
		case 3://Jumpy
		{
			Jumpy j;
			if (j.startGame())
				jumpy.push_back(j.getTS());
			break;
		}
		default:
			break;
		}
		subMenu(mode);
		break;
	case 2:
		recordMenu(mode);
		break;
	case 3:
		cout << endl << endl << "���ڷ������˵�..." << endl;
		Sleep(1200);
		mainMenu();
		break;
	default:
		cout << endl << endl << "����������..." << endl;
		Sleep(1600);
		subMenu(mode);
	}
}

void Admin::recordMenu(int mode)
{
	system("cls");
	int input;
	vector<string> records;

	switch (mode)
	{
	case 1://Reversi
	{
		records = reversi;
		break;
	}
	case 2://FiaR
	{
		records = fiar;
		break;
	}
	case 3://Jumpy
	{
		records = jumpy;
		break;
	}
	default:
		break;
	}

	if (records.empty())
	{
		cout << "���޼�¼��";
		Sleep(1200);
		subMenu(mode);
		return;
	}

	cout << "��ѡ��������Ϸ��¼��" << endl << endl;
	for (int i = 0; i < records.size(); ++i)
		cout << i + 1 << ". " << records[i] << endl;
	cout << endl;
	cin >> input;
	while (input - 1 < 0 || input - 1 >= records.size())
	{
		cout << endl << "���������룡" << endl;
		cin >> input;
	}

	switch (mode)
	{
	case 1://Reversi
	{
		Reversi r(records[input - 1]);
		if (!r.startGame())
		{
			reversi.erase(reversi.begin() + input - 1);
		}
		break;
	}
	case 2://FiaR
	{
		FIAR f(records[input - 1]);
		if (!f.startGame())
		{
			fiar.erase(fiar.begin() + input - 1);
		}
		break;
	}
	case 3://Jumpy
	{
		Jumpy j(records[input - 1]);
		if (!j.startGame())
		{
			jumpy.erase(jumpy.begin() + input - 1);
		}
		break;
	}
	default:
		break;
	}
	subMenu(mode);
}


void Admin::storeRecords()
{
	ofstream outf;

	outf.open("docs/Reversi.txt", ios::out | ios::trunc);
	for (auto fn : reversi)
		outf << fn << endl;
	outf.close();

	outf.open("docs/FiaR.txt", ios::out | ios::trunc);
	for (auto fn : fiar)
		outf << fn << endl;
	outf.close();

	outf.open("docs/Jumpy.txt", ios::out | ios::trunc);
	for (auto fn : jumpy)
		outf << fn << endl;
	outf.close();
}
