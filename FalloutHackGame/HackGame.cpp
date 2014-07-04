#include "HackGame.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctime> // Used for srand()
using namespace std;

// Constructor
HackGame::HackGame(int diff)
	: data("C:\\Users\\Julio\\Documents\\Visual Studio 2012\\FalloutHackGame\\enable.txt"),
	difficulty(diff), hOut(GetStdHandle(STD_OUTPUT_HANDLE))
{
	srand(time(NULL));
}

// Destructor
HackGame::~HackGame()
{
}

// Game logic: file will be read in and stored into a vector
// then game will start
void HackGame::beginGame()
{
	readFile();
	generateWords(gameWordsList, fullList, difficulty * 3);
	printWords(gameWordsList);
	hackWord = gameWordsList[rand() % gameWordsList.size()];
	generateGame(hackWord);

	// Set foreground color back to normal
	SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

// file will be read in into fullList vector
// if file can't be found, program will close
void HackGame::readFile()
{
	ifstream file(data);

	if(file)
	{	
		string word;

		while (!file.eof()) {
			file >> word;
			fullList.push_back(word);
		}
		file.close();
	}
	else 
	{
		// Close program if file could not be found
		cout << "File could not be found. Exiting program" << endl;
		EXIT_FAILURE;
	}
}

// Checks how many inputs are remaining after user
// has entered an input.
void HackGame::generateGame(string & word)
{
	int attempts = 4;
	string guess;

	while (attempts != 0) 
	{
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
		cout << endl << attempts << " ATTEMPT(S) LEFT: ";
		cin >> guess;

		while(guess.length() < word.length() || guess.length() > word.length())
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "\nIncorrect length, Try Again: ";
			cin >> guess;
		}

		cout << checkAnswer(word, guess) << "/" << word.length() << " correct" << endl;
		attempts--;

		if(attempts == 1)
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << endl << "CONSOLE LOCKDOWN IMMINENT!!!" << endl;
		}

		if (checkAnswer(word, guess) == word.length()) {
			cout << "____________________________" << endl;
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
			cout << "ENTRY ACCEPTED" << endl << endl;
			break;
		} 
		else
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << endl << "ENTRY DENIED" << endl << endl;
		}
	}

	if(attempts == 0)
	{
		cout << endl << "The correct password was: " << word << endl;
		cout << endl << "LOGIN FAIL. CLOSING PROGRAM..." << endl << endl;
	}	
}

// Randomly choose 10 words and store it into a list that will be
// used for the game.
void HackGame::generateWords(vector<string> & gameWordsList, const vector<string> & fullList, int wordLength)
{
	unsigned long rndNumber;
	const int NUM_OF_WORDS = 10;

	while (gameWordsList.size() != NUM_OF_WORDS) 
	{
		int divideRnd = rand() % (fullList.size() / RAND_MAX + 1);

		if (divideRnd == fullList.size() / RAND_MAX)
			rndNumber = (rand() % (fullList.size() - divideRnd * RAND_MAX)) + (divideRnd * RAND_MAX);
		else
			rndNumber = rand() + divideRnd * RAND_MAX;

		for (unsigned long i = rndNumber; i < fullList.size(); i++) {
			if (fullList[i].length() == wordLength && !ifExists(gameWordsList, fullList[i])) {
				gameWordsList.push_back(fullList[i]);
				break;
			}
		}
	}
}

bool HackGame::ifExists(const vector<string> & gameWordsList, const string & word) {
	for (auto i = 0; i < gameWordsList.size();  i++)
		if (gameWordsList[i] == word)
			return true;
	return false;
}

// returns the count of the number of correct characters between the 
// guessed word and answer
int HackGame::checkAnswer(const string & word, const string & guess)
{
	int count = 0;
	for (size_t i = 0; i < word.length(); i++)
	{
		if (toupper(word[i]) == toupper(guess[i]))
			count++;
	}

	return count;
}

// prints list of words in 2 columns
void HackGame::printWords(const vector<string> & list)
{
	for (size_t i = 0; i < list.size(); i++) {

		if(i % 2 == 0)
		{
			cout << endl << "0x" << &list[i] << "   " << list[i] << "   ";
		}
		else
		{
			cout << "0x" << &list[i] << "   " << list[i] << "   ";
		}
	}
	cout << endl;
}
