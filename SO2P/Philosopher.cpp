#include <iostream>
#include <thread>
#include "philosopher.h"
#include <mutex>

std::mutex mutexCout;

void philosopher(int id)
{
	mutexCout.lock();
	std::cout << "Philosopher nr " << id << "\n";
	mutexCout.unlock();
}
