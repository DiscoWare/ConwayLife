#include "Life.h"

char _getch(void)
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    printf("%c\n", buf);
    return buf;
 }

Board::Board()
{
	cycleCount = 0;
	for (int i = 0; i < 50; ++i)
	{
		for (int e = 0; e < 50; ++e)
		{
			board[i][e] = '.';
		}
	}
}

void Board:: print() const
{
	for (int i = 0; i < 50; ++i)
	{
		for (int e = 0; e < 50; ++e)
		{
			cout << board[i][e] << ' ';
		}
		cout << endl;
	}
}

void Board::writeToFile() const
{
	ofstream os;
	os.open("output.txt");
	for (unsigned i = 0; i < 50; i++)
	{
		for (unsigned j = 0; j < 50; j++)
		{
			os << board[i][j] << " ";
		}
		os << endl;
	}
	os << "Count: " << cycleCount << "\n\n";
	os.close();
}

void Board::GenerateRandomBoard()
{
	int y, x = 0;
	int random;
	for (unsigned i = 0; i < 50; i++)
		for (unsigned j = 0; j < 50; j++)
		{
			random = rand() % 20;
			if (random == 1)
				board[i][j] = 'O';
		}
}

void Board::readFromFile()
{
	ifstream is;
	is.open("input.txt");
	char c;
	for (unsigned i = 0; i < 50; i++)
	{
		for (unsigned j = 0; j < 50; j++)
		{
			is >> c;
			board[i][j] = c;
		}
	}
}

void recursiveGenerate()
{
	unsigned longestSequence = 0;
	Board tempBoard;
	while (true)
	{
		Board board;
		board.GenerateRandomBoard();
		tempBoard = board;
		board.scan();
		if (board.cycleCount > longestSequence)
		{
			tempBoard.cycleCount = board.cycleCount;
			tempBoard.writeToFile();
			longestSequence = board.cycleCount;
		}
	}
}

void Board::configure()
{
	char c = 's';
	Board displayBoard;
	displayBoard = *this;
	pair<int, int> current (0, 0);
	displayBoard.print();
	cout << endl;
	while (c != 'q' && c != 'r')
	{
		displayBoard.board[current.first][current.second] = board[current.first][current.second];
		c = _getch();
		switch (c)
		{
		case 'w':
		{
			if (current.first != 0)
			{
				--current.first;
			}
			break;
		}

		case 'd':
		{
			if (current.second != 49)
			{
				++current.second;
			}
			break;
		}

		case 's':
		{
			if (current.first != 49)
			{
				++current.first;
			}
			break;
		}

		case 'a':
		{
			if (current.second != 0)
			{
				--current.second;
			}
			break;
		}

		case ' ':
		{
			if (board[current.first][current.second] == '.')
			{
				board[current.first][current.second] = 'O';
			}
			else
				board[current.first][current.second] = '.';
			break;
			
		}

		case 'r':
		{
			GenerateRandomBoard();
			break;
		}

		case '0':
		{
			recursiveGenerate();
			break;
		}

		case '1':
		{
			readFromFile();
			displayBoard = *this;
			break;
		}

		}

		displayBoard.board[current.first][current.second] = '*';
		system("clear");
		displayBoard.print();
		cout << endl;
	}
}

void bufferFill(Board* buffer, unsigned size)
{
	for (unsigned i = 0; i < size; i++)
	{
		buffer[i] = Board();
	}
}

void Board::scan()
{
	Board temp;
	temp = *this;
	unsigned boardBufferSize = 50;
	Board boardBuffer[boardBufferSize];
	bufferFill(boardBuffer, boardBufferSize);
	unsigned bufferCount = 0;
	unsigned bufferIndex = 0;
	bool done = false;

	while (!done)
	{
		temp = *this;
		for (int y = 0; y < 50; ++y)
		{
			for (int x = 0; x < 50; ++x)
			{
				if (temp.board[y][x] == '.')
				{
					if (temp.countSurrounding(y, x) == 3)
					{
						(*this).board[y][x]= 'O';
					}
				}
				else
				{
					if (temp.countSurrounding(y, x) < 2 || temp.countSurrounding(y, x) > 3)
					{
						(*this).board[y][x] = '.';
					}
				}
			}
		}

		for (unsigned i = 0; i < boardBufferSize; i++)
		{
			if (*this == boardBuffer[i])
			{
				done = true;
			}
		}
		boardBuffer[bufferIndex] = *this;
		bufferIndex = (bufferIndex + 1) % boardBufferSize;


		system("clear");
		print();

		cycleCount++;
		cout << cycleCount << endl;
		usleep(300000);
	}

}

int Board::countSurrounding(int y, int x) const
{
	int count = 0;
	vector<int> yChoices = { y };
	vector<int> xChoices = { x };

	if (y != 49)
		yChoices.push_back(y + 1);
	if (y != 0)
		yChoices.push_back(y - 1);
	if (x != 0)
		xChoices.push_back(x - 1);
	if (x != 49)
		xChoices.push_back(x + 1);

	for (auto a : yChoices)
	{
		for (auto b : xChoices)
		{
			if (board[a][b] == 'O')
			{
				++count;
			}
		}
	}
	if (board[y][x] == 'O')
		--count;

	return count;
}

Board& Board::operator=(const Board& rBoard)
{
	for (int i = 0; i < 50; ++i)
	{
		for (int j = 0; j < 50; ++j)
		{
			board[i][j] = rBoard.board[i][j];
		}
	}

	return *this;
}

bool Board::operator==(const Board& rBoard) const
{
	for (unsigned i = 0; i < 50; i++)
		for (unsigned j = 0; j < 50; j++)
		{
			if (board[i][j] != rBoard.board[i][j])
				return false;
		}
	return true;
}
