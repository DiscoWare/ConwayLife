#include "Life.h"

int main()
{
	srand (time(NULL));
	Board thisBoard;
	thisBoard.configure();
	thisBoard.scan();

	// system("Pause");
	return 0;
}