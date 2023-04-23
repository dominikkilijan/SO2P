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

extern int phy[5];
extern int phx[5];
extern char symbol[5];

void philosopher(int id, Chopstick *chopstick, WINDOW* window, int y, int x)
{
	//do {
		// pauza zeby zobaczyc jak to wyglada na start
		std::this_thread::sleep_for(1s);


		// chwytanie lewego albo prawego chopsticka w zaleznosci od parzystosci - zapobieganie deadlockom
		if (id % 2 == 0)
		{
			// jego prawy 
			chopstick[id].wait();
			if (id == 2)
				mvwprintw(window, y, x+5, "\\");	
			else if (id == 4)
				mvwprintw(window, y+1, x+2, "/");
			else 
				mvwprintw(window, y, x-1, "/");
			
			wrefresh(window);
			std::this_thread::sleep_for(1s);

			// jego lewy
			chopstick[(id + 1) % 5].wait();
			if (id == 2)
				mvwprintw(window, y, x-1, "/");	
			else if (id == 4)
				mvwprintw(window, y-1, x+2, "\\");
			else 
				mvwprintw(window, y, x+5, "\\");
			
			wrefresh(window);
			std::this_thread::sleep_for(1s);
		}
		else
		{
			// jego lewy
			chopstick[(id + 1) % 5].wait();
			if(id == 1)
				mvwprintw(window, y+1, x+2, "\\");	
			else 
				mvwprintw(window, y, x-1, "/");
			wrefresh(window);
			std::this_thread::sleep_for(1s);
			
			// jego prawy
			chopstick[id].wait();
			if (id == 1)
				mvwprintw(window, y-1, x+2, "/");
			else
				mvwprintw(window, y, x+5, "\\");	
			
			wrefresh(window);
			std::this_thread::sleep_for(1s);
		}
		
		// jedzenie
		std::this_thread::sleep_for(2s);

		//if (id == 0)
		//{
			// odkladanie jego prawego chopsticka
			chopstick[id].signal(id, 'r');
			if (id == 1)
				mvwprintw(window, y-1, x+2, ".");
			else if (id == 4)
				mvwprintw(window, y+1, x+2, ".");
			else
				mvwprintw(window, y, x-1, ".");
			wrefresh(window);
	
			std::this_thread::sleep_for(1s);

			// odkladanie jego lewego chopsticka
			chopstick[(id + 1) % 5].signal(id, 'l');
			if (id == 1)
				mvwprintw(window, y+1, x+2, ".");
			else if (id == 4)
				mvwprintw(window, y-1, x+2, ".");
			else
				mvwprintw(window, y, x+5, ".");
			wrefresh(window);

			std::this_thread::sleep_for(1s);
		//}
		/* else
		{
			// odkladanie lewego chopsticka
			chopstick[id].signal(id, 'r');
			mvwprintw(window, y, x-1, ".");
			wrefresh(window);
	
			std::this_thread::sleep_for(1s);

			// odkladanie prawego chopsticka
			chopstick[(id + 1) % 5].signal(id, 'l');
			mvwprintw(window, y, x+3, ".");
			wrefresh(window);

			std::this_thread::sleep_for(1s);
		} */
		// myslenie
		std::this_thread::sleep_for(2s);
	//} while (true);
}
