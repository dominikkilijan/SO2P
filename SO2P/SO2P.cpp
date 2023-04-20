#include <iostream>
#include "Philosopher.h"
#include <thread>
#include "Chopstick.h"
#include <ncurses.h>

Chopstick chopstick[5];

int main()
{
    // watki zachowujace sie jak filozofowie (jedzenie i myslenie)
    /*
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
    */

    initscr();			/* Start curses mode 		  */
    noecho();
    cbreak();

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

    // paleczki na stole
    mvwprintw(dTable, 1, 3, "\\");  //0
    mvwprintw(dTable, 1, 11, "/");  //1
    mvwprintw(dTable, 6, 12, "\\"); //2
    mvwprintw(dTable, 6, 7, "|");   //3
    mvwprintw(dTable, 6, 2, "/");   //4

    wrefresh(window);
    wrefresh(dTable);

//	printw("Hello World !!!");	/* Print Hello World		  */
	getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */

}
