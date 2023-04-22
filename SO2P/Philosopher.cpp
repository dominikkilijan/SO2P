#include <iostream>
#include <thread>
#include "Philosopher.h"
#include <mutex>
#include "Chopstick.h"
#include <chrono>
#include <ncurses.h>

using namespace std::chrono_literals;

// mutex zapobiegajacy nakladaniu sie tekstow w konsoli
std::mutex mutexCout;

void philosopher(int id, Chopstick *chopstick, WINDOW* window, int y, int x)
{
	//do {
		// pauza zeby zobaczyc jak to wyglada na start
		std::this_thread::sleep_for(1s);


		// chwytanie lewego albo prawego chopsticka w zaleznosci od parzystosci - zapobieganie deadlockom
		if (id % 2 == 0)
		{
			// lewy
			chopstick[id].wait();
			if (id == 2 || id == 4)
				mvwprintw(window, y, x+3, "\\");	
			else mvwprintw(window, y, x-1, "/");
			wrefresh(window);
			std::this_thread::sleep_for(1s);

			// prawy
			chopstick[(id + 1) % 5].wait();
			if (id == 2 || id == 4)
				mvwprintw(window, y, x-1, "/");	
			else mvwprintw(window, y, x+3, "\\");
			wrefresh(window);
			std::this_thread::sleep_for(1s);
		}
		else
		{
			// prawy
			chopstick[(id + 1) % 5].wait();
			if (id == 1 || id == 3)
				mvwprintw(window, y, x-1, "/");	
			else mvwprintw(window, y, x+3, "\\");
			wrefresh(window);
			std::this_thread::sleep_for(1s);
			
			// lewy
			chopstick[id].wait();
			if (id == 1 || id == 3)
				mvwprintw(window, y, x+3, "\\");	
			else mvwprintw(window, y, x-1, "/");
			wrefresh(window);
			std::this_thread::sleep_for(1s);
		}
		
		// jedzenie
		std::this_thread::sleep_for(2s);

		// odkladanie lewego chopsticka
		chopstick[id].signal(id);
		mvwprintw(window, y, x-1, ".");
		wrefresh(window);
	
		std::this_thread::sleep_for(1s);

		// odkladanie prawego chopsticka
		chopstick[(id + 1) % 5].signal(id);
		mvwprintw(window, y, x+3, ".");
		wrefresh(window);

		std::this_thread::sleep_for(1s);

		// myslenie
		std::this_thread::sleep_for(2s);
	//} while (true);
}
