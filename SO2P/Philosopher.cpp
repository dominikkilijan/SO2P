#include <iostream>
#include <thread>
#include "philosopher.h"
#include <mutex>
#include "Chopstick.h"

std::mutex mutexCout;

void philosopher(int id, Chopstick *chopstick)
{
	mutexCout.lock();
	std::cout << "Philosopher nr " << id << "\n";
	//chopstick[id].wait();

	for (int i = 0; i < 5; i++)
	{
		chopstick[i].printValue();
	}
	/*chopstick[id].signal();

	for (int i = 0; i < 5; i++)
	{
		chopstick[i].printValue();
	}*/

	mutexCout.unlock();


	/*for (int i = 0; i < 5; i++)
	{
		std::cout << i << ". ";
		chopstick[i].printValue();
	}*/

	// grab left chopstick

	// grab right chopstick

	// eat

	// leave left chopstick

	// leave right chopstick

}
