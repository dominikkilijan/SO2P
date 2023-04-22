#include <iostream>
#include "Philosopher.h"
#include <thread>
#include "Chopstick.h"
#include <ncurses.h>
#include <chrono>

int main()
{
    initscr();			/* Start curses mode 		  */
    noecho();
    cbreak();
    curs_set(0);

    // wielkosc ekranu
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    // tworzenie okna
    WINDOW * window = newwin(20, 50, (yMax/2)-10, 15);
    box(window, 0, 0);
    refresh();
    wrefresh(window);    

    // graficzka stolu
    WINDOW * dTable = newwin(8, 15, 8, 33);
    box(dTable, 0, 0);
    refresh();
    wrefresh(dTable);

    // glowy filozofow
    mvwprintw(window, 5, 23, "(0)");
    mvwprintw(window, 9, 34, "(1)");
    mvwprintw(window, 14, 27, "(2)");
    mvwprintw(window, 14, 19, "(3)");
    mvwprintw(window, 9, 13, "(4)");
    //wrefresh(window);

    // paleczki na stole
    Chopstick chopstick[] = {Chopstick(dTable, 1,3, '\\'), 
                             Chopstick(dTable, 1,11, '/'), 
                             Chopstick(dTable, 6,12, '\\'), 
                             Chopstick(dTable, 6,7, '|'), 
                             Chopstick(dTable, 6,2, '/') };


    /*mvwprintw(dTable, 1, 3, "\\");  //0
    mvwprintw(dTable, 1, 11, "/");  //1
    mvwprintw(dTable, 6, 12, "\\"); //2
    mvwprintw(dTable, 6, 7, "|");   //3
    mvwprintw(dTable, 6, 2, "/");   //4
    */
    // watki zachowujace sie jak filozofowie (jedzenie i myslenie)
    std::thread ph1(philosopher, 0, chopstick);
    std::thread ph2(philosopher, 1, chopstick);
    std::thread ph3(philosopher, 2, chopstick);
    std::thread ph4(philosopher, 3, chopstick);
    std::thread ph5(philosopher, 4, chopstick);

    ph1.join();
    ph2.join();
    ph3.join();
    ph4.join();
    ph5.join();
    

	getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */

}
