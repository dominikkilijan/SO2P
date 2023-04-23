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
	// Chopstick zna lokalizacje i symbol nastepnego Chopsticka (4. zna 0.)
	int xNext, yNext;
	char characterNext;
	// Stol na ktorym bedzie lezec
	WINDOW* dTable;

public:
	Chopstick(WINDOW* window, int yLoc, int xLoc, char charSymbol, int yNextLoc, int xNextLoc, char characterNextLoc);
	void wait();
	void signal(int id, char side);
	void printValue();
	void setValue(int val);
};

