#include "Chopstick.h"
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <ncurses.h>
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

std::mutex m;
std::condition_variable cv;

// konstruktor
Chopstick::Chopstick(WINDOW* window, int yLoc, int xLoc, char charSymbol)
{
	dTable = window;
	y = yLoc;
	x = xLoc;
	character = charSymbol;
	// poczatkowe polozenie na stole
	mvwaddch(dTable, y, x, character);
	wrefresh(dTable);
}

// Funkcje semafora
	
	// podnoszenie paleczki (funkcja P)
	void Chopstick::wait()
	{
		std::unique_lock<decltype(m)> lock(m);
		while (!value)
			cv.wait(lock);
		--value;
		// paleczka znika ze stolu
		mvwprintw(dTable, y, x, " ");
		wrefresh(dTable);
	}

	// odkladanie paleczki (funkcja V)
	void Chopstick::signal(int id)
	{
		std::lock_guard<decltype(m)> lock(m);
		
		// paleczka pojawia sie na stole
		mvwaddch(dTable, y, x, character);
		wrefresh(dTable);
		//std::this_thread::sleep_for(1s);
		
		++value;
		cv.notify_all(); // idk czy w tym przypadku to jest jakas wielka roznica czy jest _one czy _all
	}

	// funkcje do testowania czy wszystko dziala
	void Chopstick::printValue()
	{
		std::cout << value << std::endl;
	}

	void Chopstick::setValue(int val)
	{
		value = val;
	}