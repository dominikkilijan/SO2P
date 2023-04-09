#include <iostream>
#include "philosopher.h"
#include <thread>
#include "Chopstick.h"

Chopstick chopstick[5];

int main()
{
    chopstick[0].printValue();
    chopstick[1].printValue();
    chopstick[2].printValue();
    chopstick[3].printValue();
    chopstick[4].printValue();
    
    chopstick[1].setValue(3);
    
    chopstick[0].printValue();
    chopstick[1].printValue();
    chopstick[2].printValue();
    chopstick[3].printValue();
    chopstick[4].printValue();


    std::thread ph1(philosopher, 1, chopstick);
    std::thread ph2(philosopher, 2, chopstick);
    std::thread ph3(philosopher, 3, chopstick);
    std::thread ph4(philosopher, 4, chopstick);
    std::thread ph5(philosopher, 5, chopstick);

    ph1.join();
    ph2.join();
    ph3.join();
    ph4.join();
    ph5.join();

}
