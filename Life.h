#pragma once
// #include <conio.h>
#include <iostream>
#include <time.h>
#include <utility>
#include <vector>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <termios.h>
#include <fstream>
// #include <windows.h>
using namespace std;

struct Board
{
	Board();
	char board[50][50];
	unsigned cycleCount;

	void scan();
	void configure();
	void GenerateRandomBoard();
	void readFromFile();
	int countSurrounding(int y, int x) const;
	void print() const;
	void writeToFile() const;

	bool operator==(const Board& rBoard) const;
	Board& operator=(const Board& rBoard);
};

void print(char c[50][50]);