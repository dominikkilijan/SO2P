#include <iostream>
#include <thread>
#include "philosopher.h"
#include <mutex>
#include "Chopstick.h"
#include <chrono>

using namespace std::chrono_literals;

// mutex zapobiegajacy nakladaniu sie tekstow w konsoli
std::mutex mutexCout;

void philosopher(int id, Chopstick *chopstick)
{
	//do {
		mutexCout.lock();
		std::cout << "Philosopher nr " << id << "\n";
		mutexCout.unlock();
		


		// chwytanie lewego albo prawego chopsticka w zaleznosci od parzystosci - zapobieganie deadlockom
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
		
		// jedzenie
		mutexCout.lock();
		std::cout << id << ". Omnomnomnom\n";
		mutexCout.unlock();
		std::this_thread::sleep_for(2s);

		// odkladanie lewego chopsticka
		mutexCout.lock();
		std::cout << id << ". Pojedzone\n";
		mutexCout.unlock();
		chopstick[id].signal();

		// odkladanie prawego chopsticka
		chopstick[(id + 1) % 5].signal();

		// myslenie
		mutexCout.lock();
		std::cout << id << ". Hmmm\n";
		mutexCout.unlock();
		std::this_thread::sleep_for(2s);
	//} while (true);
}
