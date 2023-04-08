#include <iostream>
#include <thread>
#include "philosopher.h"
#include <mutex>

std::mutex mutexCout;

void philosopher(int id)
{

	for (int i = 0; i < 5; i++)
	{
		mutexCout.lock();
		std::cout << "Philosopher nr " << id << "\n";
		mutexCout.unlock();
	}
}
