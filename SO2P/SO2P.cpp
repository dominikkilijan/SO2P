#include <iostream>
#include "philosopher.h"
#include <thread>
#include "Chopstick.h"

Chopstick chopstick[5];

int main()
{
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

}
