#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <Windows.h>
#include <algorithm>
#include <conio.h>
#include <ctime>
#include <fstream>
#include <string>
using namespace std;

struct Position
{
	int x, y;
	Position(int x, int y) :x(x), y(y) {}
	Position() :x(0), y(0) {}
};

enum Color
{
	BLACK, WHITE, EMPTY
};


void go_to(int x, int y);