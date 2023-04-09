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
		mutexCout.lock();
		std::cout << id << ". Glodny jestem\n";
		mutexCout.unlock();
		// grab left chopstick
		chopstick[id].wait();
		// grab right chopstick
		chopstick[(id + 1) % 5].wait();
		// eat
		mutexCout.lock();
		std::cout << id << ". Omnomnomnom\n";
		mutexCout.unlock();
		std::this_thread::sleep_for(2s);
		// leave left chopstick
		chopstick[id].signal();
		// leave right chopstick
		chopstick[(id + 1) % 5].signal();
		mutexCout.lock();
		std::cout << id << ". Pojedzone\n";
		mutexCout.unlock();
	//} while (true);
}
