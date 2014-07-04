#include <iostream>
#include "HackGame.h"
using namespace std;

void main()
{
	int diff;

	cout << "FALLOUT INDUSTRIES (TM) TERMALINK PROTOCOL" << endl;
	cout << "ENTER DIFFICULTY(1 - 5): ";
	cin >> diff;

	cout << endl << "OPENING TERMINAL. ENTER CREDENTIALS TO PROCEED..." 
		<< endl << endl;

	HackGame *game;
	game = new HackGame(diff);

	game->beginGame();

	delete game;
}
