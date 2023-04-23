#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <ncurses.h>
#include "Philosopher.h"
#include "Chopstick.h"

using namespace std::chrono_literals;

// mutex zapobiegajacy przeskakiwaniu znakow w animacji
std::mutex phM;

extern int phy[5];
extern int phx[5];
extern char symbol[5];

void philosopher(int id, Chopstick *chopstick, WINDOW* window, int y, int x)
{
	//do {
		// pauza zeby zobaczyc jak to wyglada na start
		std::this_thread::sleep_for(1s);

		// chwytanie lewego albo prawego chopsticka w zaleznosci od parzystosci - zapobieganie deadlockom (jesli id jest parzyste to zaczyna od prawego)
		if (id % 2 == 0)
		{
			// jego prawy
			//phM.lock(); // mozna sprobowac usunac mutex z chopstick w takim razie (jesli to nie zadzialą)
			chopstick[id].wait();
			//phM.unlock(); 

			if (id == 2)
			{
				phM.lock();
				mvwaddch(window, y, x+5, symbol[id]);
				wrefresh(window);
				phM.unlock(); 	
			}
			else if (id == 4)
			{
				phM.lock();
				mvwaddch(window, y+1, x+2, symbol[id]);
				wrefresh(window);
				phM.unlock();
			}
			else 
			{
				phM.lock();
				mvwaddch(window, y, x-1, symbol[id]);
				wrefresh(window);
				phM.unlock();
			}
			wrefresh(window);
			std::this_thread::sleep_for(1s);

			// jego lewy
			//phM.lock();
			chopstick[(id + 1) % 5].wait();
			//phM.unlock();
			if (id == 2)
			{
				phM.lock();	
				mvwaddch(window, y, x-1, symbol[(id+1)%5]);
				wrefresh(window);
				phM.unlock();
			}
			else if (id == 4)
			{
				phM.lock();
				mvwaddch(window, y-1, x+2, symbol[(id+1)%5]);
				wrefresh(window);
				phM.unlock();
			}
			else 
			{
				phM.lock();
				mvwaddch(window, y, x+5, symbol[(id+1)%5]);
				wrefresh(window);
				phM.unlock();
			}
			wrefresh(window);
			std::this_thread::sleep_for(1s);
		}
		else
		{
			// jego lewy
			//phM.lock();
			chopstick[(id + 1) % 5].wait();
			//phM.unlock();
			if(id == 1)
			{
				phM.lock();	
				mvwaddch(window, y+1, x+2, symbol[(id+1)%5]);
				wrefresh(window);
				phM.unlock();
			}
			else 
			{
				phM.lock();
				mvwaddch(window, y, x-1, symbol[(id+1)%5]);
				wrefresh(window);
				phM.unlock();
			}
			wrefresh(window);
			std::this_thread::sleep_for(1s);
			
			// jego prawy
			//phM.lock();
			chopstick[id].wait();
			//phM.unlock();
			if (id == 1)
			{
				phM.lock();
				mvwaddch(window, y-1, x+2, symbol[id]);
				wrefresh(window);
				phM.unlock();
			}
			else
			{
				phM.lock();	
				mvwaddch(window, y, x+5, symbol[id]);
				wrefresh(window);
				phM.unlock();
			}
			wrefresh(window);
			std::this_thread::sleep_for(1s);
		}
		
		// jedzenie
		std::this_thread::sleep_for(2s);

		// odkladanie jego prawego chopsticka
		//phM.lock();
		chopstick[id].signal(id, 'r');
		//phM.unlock();
		if (id == 1)
		{
			phM.lock();
			mvwprintw(window, y-1, x+2, "r");
			wrefresh(window);
			phM.unlock();
		}
		else if (id == 4)
		{
			phM.lock();
			mvwprintw(window, y+1, x+2, "r");
			wrefresh(window);
			phM.unlock();
		}
		else if (id == 0)
		{
			phM.lock();
			mvwprintw(window, y, x-1, "r");
			wrefresh(window);
			phM.unlock();
		}
		else
		{
			phM.lock();
			mvwprintw(window, y, x+5, "r");
			wrefresh(window);
			phM.unlock();
		}	
		wrefresh(window);
	
		std::this_thread::sleep_for(1s);

		// odkladanie jego lewego chopsticka
		//phM.lock();
		chopstick[(id + 1) % 5].signal(id, 'l');
		//phM.unlock();
		if (id == 1)
		{
			phM.lock();
			mvwprintw(window, y+1, x+2, "l");
			wrefresh(window);
			phM.unlock();
		}
		else if (id == 4)
		{
			phM.lock();
			mvwprintw(window, y-1, x+2, "l");
			wrefresh(window);
			phM.unlock();
		}
		else if (id == 0)
		{
			phM.lock();
			mvwprintw(window, y, x+5, "l");
			wrefresh(window);
			phM.unlock();
		}
		else
		{
			phM.lock();
			mvwprintw(window, y, x-1, "l");
			wrefresh(window);
			phM.unlock();
		}
		wrefresh(window);

		std::this_thread::sleep_for(1s);
		
		// myslenie
		std::this_thread::sleep_for(2s);
	//} while (true);
}
