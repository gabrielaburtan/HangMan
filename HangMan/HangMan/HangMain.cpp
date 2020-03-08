#include "Hangman.h"
#include <iostream>

int main()
{
	Hangman m;
	m.printMessage("HANG MAN",true,true);
	m.DrawHangMan(8);
	m.printMessage("AVAILABLE LETTERS", true, true);
	system("pause");
	return 0;
}