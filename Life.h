#pragma once
#include <conio.h>
#include <iostream>
#include <utility>
#include <vector>
#include <chrono>
#include <thread>
#include <windows.h>
using namespace std;

struct Board
{
	Board();
	char board[50][50];
	
	void scan();
	void configure();
	int countSurrounding(int y, int x);
	void print() const;

	Board& operator=(const Board& rBoard);
};

void print(char c[50][50]);