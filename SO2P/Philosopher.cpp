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
// wspolrzedne glow filozofow
extern int phy[5], phx[5];
// wspolrzedne paleczek
extern int chy[5], chx[5];
// symbole paleczek
extern char symbol[5];
// nosy filozofow
extern char nose[5];

void philosopher(int id, Chopstick *chopstick, WINDOW* window, WINDOW* dTable, int y, int x)
{
	do {
		// pauza zeby zobaczyc jak to wyglada na start
		std::this_thread::sleep_for(1s);

		// chwytanie lewego albo prawego chopsticka w zaleznosci od parzystosci - zapobieganie deadlockom (jesli id jest parzyste to zaczyna od prawego)
		if (id % 2 == 0)
		{
			// jego prawy
			chopstick[id].wait();		
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
			else // 0
			{
				phM.lock();
				mvwaddch(window, y, x-1, '/');
				wrefresh(window);
				phM.unlock();
			}
			// znikanie paleczki ze stolu
			phM.lock();
			mvwaddch(dTable, chy[id], chx[id], ' ');
			wrefresh(dTable);
			phM.unlock();
			wrefresh(window);
			std::this_thread::sleep_for(1s);

			// jego lewy
			//phM.lock();
			chopstick[(id + 1) % 5].wait();
			//phM.unlock();
			if (id == 2)
			{
				phM.lock();	
				mvwaddch(window, y, x-1, '/');
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
				mvwaddch(window, y, x+5, '\\');
				wrefresh(window);
				phM.unlock();
			}

			// znikanie paleczki ze stolu
			phM.lock();
			mvwaddch(dTable, chy[(id + 1) % 5], chx[(id + 1) % 5], ' ');
			wrefresh(dTable);
			phM.unlock();
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
			// znikanie paleczki ze stolu
			phM.lock();
			mvwaddch(dTable, chy[(id + 1) % 5], chx[(id + 1) % 5], ' ');
			wrefresh(dTable);
			phM.unlock();
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
			else // 3
			{
				phM.lock();	
				mvwaddch(window, y, x+5, '\\');
				wrefresh(window);
				phM.unlock();
			}
			// znikanie paleczki ze stolu
			phM.lock();
			mvwaddch(dTable, chy[id], chx[id], ' ');
			wrefresh(dTable);
			phM.unlock();
			wrefresh(window);
			std::this_thread::sleep_for(1s);
		}
		
		// jedzenie
		phM.lock();
		mvwaddch(window, phy[id], phx[id]+2,'o');
		wrefresh(window);
		phM.unlock();
		std::this_thread::sleep_for(2s);
		phM.lock();
		mvwaddch(window, phy[id], phx[id]+2, nose[id]);
		wrefresh(window);
		phM.unlock();

		// odkladanie jego prawego chopsticka
		//phM.lock();
		chopstick[id].signal(id, 'r');
		//phM.unlock();
		if (id == 1)
		{
			phM.lock();
			mvwprintw(window, y-1, x+2, " ");
			wrefresh(window);
			phM.unlock();
		}
		else if (id == 4)
		{
			phM.lock();
			mvwprintw(window, y+1, x+2, " ");
			wrefresh(window);
			phM.unlock();
		}
		else if (id == 0)
		{
			phM.lock();
			mvwprintw(window, y, x-1, " ");
			wrefresh(window);
			phM.unlock();
		}
		else
		{
			phM.lock();
			mvwprintw(window, y, x+5, " ");
			wrefresh(window);
			phM.unlock();
		}
		// wyswietlanie paleczki na stole
		phM.lock();
		mvwaddch(dTable, chy[id], chx[id], symbol[id]);
		wrefresh(dTable);
		phM.unlock();	
		wrefresh(window);
	
		std::this_thread::sleep_for(1s);

		// odkladanie jego lewego chopsticka
		//phM.lock();
		chopstick[(id + 1) % 5].signal(id, ' ');
		//phM.unlock();
		if (id == 1)
		{
			phM.lock();
			mvwprintw(window, y+1, x+2, " ");
			wrefresh(window);
			phM.unlock();
		}
		else if (id == 4)
		{
			phM.lock();
			mvwprintw(window, y-1, x+2, " ");
			wrefresh(window);
			phM.unlock();
		}
		else if (id == 0)
		{
			phM.lock();
			mvwprintw(window, y, x+5, " ");
			wrefresh(window);
			phM.unlock();
		}
		else
		{
			phM.lock();
			mvwprintw(window, y, x-1, " ");
			wrefresh(window);
			phM.unlock();
		}
		// wyswietlanie paleczki na stole
		phM.lock();
		mvwaddch(dTable, chy[(id+1)%5], chx[(id+1)%5], symbol[(id+1)%5]);
		wrefresh(dTable);
		phM.unlock();
		wrefresh(window);

		std::this_thread::sleep_for(1s);
		
		// myslenie
		std::this_thread::sleep_for(2s);
	//} while (wgetch(window) != 'x');
	} while(true);
}