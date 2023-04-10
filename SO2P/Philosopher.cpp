#include <iostream>
#include <thread>
#include "philosopher.h"
#include <mutex>
#include "Chopstick.h"
#include <chrono>

using namespace std::chrono_literals;

std::mutex mutexCout;

void philosopher(int id, Chopstick *chopstick)
{
	//do {
		mutexCout.lock();
		std::cout << "Philosopher nr " << id << "\n";
		mutexCout.unlock();
		


		// grab left then right chopstick or right then left depending on pairity of id
		if (id % 2 == 0)
		{
			chopstick[id].wait();
			
			mutexCout.lock();
			std::cout << id << ". Glodny jestem\n";
			mutexCout.unlock();
			
			chopstick[(id + 1) % 5].wait();
		}
		else
		{
			chopstick[(id + 1) % 5].wait();
			
			mutexCout.lock();
			std::cout << id << ". Glodny jestem\n";
			mutexCout.unlock();
			
			chopstick[id].wait();
		}
		
		// eat
		mutexCout.lock();
		std::cout << id << ". Omnomnomnom\n";
		mutexCout.unlock();
		std::this_thread::sleep_for(2s);

		// leave left chopstick
		mutexCout.lock();
		std::cout << id << ". Pojedzone\n";
		mutexCout.unlock();
		chopstick[id].signal();
		// leave right chopstick
		chopstick[(id + 1) % 5].signal();

		// think
		mutexCout.lock();
		std::cout << id << ". Hmmm\n";
		mutexCout.unlock();
		std::this_thread::sleep_for(2s);
	//} while (true);
}
