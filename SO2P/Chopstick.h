#pragma once
#include <ncurses.h>

class Chopstick
{
private:
	// Na start chopstick jest dostepny do uzycia
	int value = 1;
	// Chopstick zna swoja lokalizacje i symbol na grafice
	int x, y;
	char character;
	// Stol na ktorym bedzie lezec
	WINDOW* dTable;

public:
	Chopstick(WINDOW* window, int yLoc, int xLoc, char charSymbol);
	void wait();
	void signal();
	void printValue();
	void setValue(int val);
};

