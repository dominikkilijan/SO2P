#pragma once
#include "Chopstick.h"
#include <ncurses.h>

void philosopher(int id, Chopstick *chopstick, WINDOW* window, WINDOW* dTable, int y, int x);

