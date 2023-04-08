#include <iostream>
#include "philosopher.h"
#include <thread>

int main()
{
    std::thread ph1(philosopher, 1);
    std::thread ph2(philosopher, 2);
    std::thread ph3(philosopher, 3);
    
    ph1.join();
    ph2.join();
    ph3.join();
}
