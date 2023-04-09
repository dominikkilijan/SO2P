#include <iostream>
#include "philosopher.h"
#include <thread>
#include "Chopstick.h"

Chopstick chopstick[5];

int main()
{
    std::thread ph1(philosopher, 1);
    std::thread ph2(philosopher, 2);
    std::thread ph3(philosopher, 3);
    std::thread ph4(philosopher, 4);
    std::thread ph5(philosopher, 5);

    ph1.join();
    ph2.join();
    ph3.join();
    ph4.join();
    ph5.join();
}
