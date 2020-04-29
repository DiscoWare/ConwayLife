#pragma once
// #include <conio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <utility>
#include <vector>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <cstdlib>
#include <termios.h>
// #include <windows.h>
using namespace std;

struct Board
{
	Board();
	char board[50][50];
	
	void scan();
	void configure();
	void GenerateRandomBoard();
	int countSurrounding(int y, int x);
	void print() const;

	Board& operator=(const Board& rBoard);
};

void print(char c[50][50]);