#include <iostream>
#include "Philosopher.h"
#include <thread>
#include "Chopstick.h"
#include <ncurses.h>
#include <chrono>


// wpolrzedne dla chopstick
int chy[5] = {1,1,6,6,6};
int chx[5] = {3,11,12,7,2};

// wspolrzedne dla philosopher
int phy[5] = {5,9,14,14,9};
int phx[5] = {23,34,27,19,12};

// symbole chopstickow
char symbol[5] = {'0' , '1' , '2' , '3' , '4'};//{'\\' , '/' , '\\' , '|' , '/'};//

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
    mvwprintw(window, phy[0], phx[0], "(*v*)");
    mvwprintw(window, phy[1], phx[1], "(*<*)");
    mvwprintw(window, phy[2], phx[2], "(*^*)");
    mvwprintw(window, phy[3], phx[3], "(*^*)");
    mvwprintw(window, phy[4], phx[4], "(*>*)");
    wrefresh(window);

    // paleczki na stole
    Chopstick chopstick[] = {Chopstick(dTable, chy[0], chx[0], symbol[0], chy[1], chx[1], symbol[1]), 
                             Chopstick(dTable, chy[1], chx[1], symbol[1], chy[2], chx[2], symbol[2]), 
                             Chopstick(dTable, chy[2], chx[2], symbol[2], chy[3], chx[3], symbol[3]), 
                             Chopstick(dTable, chy[3], chx[3], symbol[3], chy[4], chx[4], symbol[4]), 
                             Chopstick(dTable, chy[4], chx[4], symbol[4], chy[0], chx[0], symbol[0]) };


    // watki zachowujace sie jak filozofowie (jedzenie i myslenie)
    std::thread ph0(philosopher, 0, chopstick, window, dTable, phy[0], phx[0]);
    std::thread ph1(philosopher, 1, chopstick, window, dTable, phy[1], phx[1]);
    std::thread ph2(philosopher, 2, chopstick, window, dTable, phy[2], phx[2]);
    std::thread ph3(philosopher, 3, chopstick, window, dTable, phy[3], phx[3]);
    std::thread ph4(philosopher, 4, chopstick, window, dTable, phy[4], phx[4]);

    ph0.join();
    ph1.join();
    ph2.join();
    ph3.join();
    ph4.join();
    

	getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */

}
