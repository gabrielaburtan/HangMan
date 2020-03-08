#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <time.h>

void printMessage(std::string msg, bool printTop = true, bool printBottom = true)
{
	if (printTop)
	{
		std::cout << "+---------------------------------+" << std::endl;
		std::cout << "|";
	}
	else
		std::cout << "|";
	bool front = true;
	for (int i = msg.length(); i < 33; i++)
	{
		if (front)
		{
			msg = " " + msg;
		}
		else
		{
			msg = msg + " ";
		}
		front = !front;
	}
	std::cout << msg;
	if (printBottom)
	{
		std::cout << "|" << std::endl;
		std::cout << "+---------------------------------+" << std::endl;
	}
	else
		std::cout << "|" << std::endl;
}

void drawHangMan(int guessCount = 0)
{
	if (guessCount >= 1)
		printMessage("|", false, false);
	else
		printMessage(" ", false, false);
	if (guessCount >= 2)
		printMessage("O", false, false);
	else
		printMessage(" ", false, false);
	if (guessCount == 3)
		printMessage("/  ", false, false);
	if (guessCount == 4)
		printMessage("/| ", false, false);
	if (guessCount >= 5)
		printMessage("/|\\", false, false);
	else
		printMessage(" ", false, false);
	if (guessCount == 6)
		printMessage("/  ", false, false);
	if (guessCount > 6)
		printMessage("/ \\", false, false);
	else
		printMessage(" ", false, false);
}
void printLetters(std::string input, char from, char to)
{
	std::string s;
	for (char it = from; it <= to; it++)
	{
		if (input.find(it) == std::string::npos)
		{
			s += it;
			s += " ";
		}
		else
			s += "  ";
	}
	printMessage(s, false, false);
}
void availableLetters(std::string word)
{
	printLetters(word, 'A', 'M');
	printLetters(word, 'N', 'Z');
}
bool check(std::string word, std::string guessed)
{
	bool won = true;
	std::string s;
	for (auto it : word)
	{
		if (guessed.find(it) == std::string::npos)
		{
			won = false;
			s += "_ ";
		}
		else
		{
			s += it;
			s += " ";
		}
	}
	printMessage(s, false);
	return won;
}
std::string getRandomWord(std::string path)
{
	std::string word;
	std::vector<std::string> vec;
	std::ifstream read(path);
	if (read.is_open())
	{
		while (std::getline(read, word))
			vec.push_back(word);
		int random = rand() % vec.size();
		word = vec.at(random);
		read.close();
	}
	return word;
}
int triesLeft(std::string word, std::string guessed)
{
	int err = 0;
	for (auto it : guessed)
	{
		if (word.find(it) == std::string::npos)
			err++;
	}
	return err;
}
int main()
{
	srand(time(0));
	std::string guessWord = getRandomWord("words.txt");
	std::string guessed;
	int tries = 0;
	bool win = false;
	do
	{
		system("cls");
		printMessage("HANG MAN", true, true);
		drawHangMan(tries);
		printMessage("AVAILABLE LETTERS", true, true);

		availableLetters(guessed);
		printMessage("Guess the word!", true, true);
		win = check(guessWord, guessed);

		if (win)
			break;

		char x;
		std::cout << "Type a letter: ";
		std::cin >> x;
		if (guessed.find(x) == std::string::npos)
			guessed += x;

		tries = triesLeft(guessWord, guessed);
		if (tries == 7)
		{
			printMessage("YOU LOSE!", true, true);
		}
	} while (tries <= 7);
	if (win)
		printMessage("YOU WON!");
	return 0;
}