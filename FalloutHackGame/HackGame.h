#pragma once
#ifndef HACKGAME_H
#define HACKGAME_H
#include <string>
#include <vector>
#include <Windows.h>

class HackGame
{
	public:
		HackGame(int);
		~HackGame();

		void beginGame();

	private:
		/* Class Variables */
		const std::string data;
		std::string hackWord;
		int difficulty;
		std::vector<std::string> fullList, gameWordsList;
		HANDLE hOut; // used for color output

		/* Class methods that the class should only have access to */
		void readFile();
		void generateGame(std::string &);
		void generateWords(std::vector<std::string> &, const std::vector<std::string> &, int);
		bool ifExists(const std::vector<std::string> &, const std::string &);
		int checkAnswer(const std::string &, const std::string &);
		void printWords(const std::vector<std::string> &);
};

#endif