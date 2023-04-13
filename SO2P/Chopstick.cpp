#include "Chopstick.h"
#include <mutex>
#include <condition_variable>
#include <iostream>

std::mutex m;
std::condition_variable cv;

// Funkcje semafora
	
	// podnoszenie paleczki (funkcja P)
	void Chopstick::wait()
	{
		std::unique_lock<decltype(m)> lock(m);
		while (!value)
			cv.wait(lock);
		--value;
	}

	// odkladanie paleczki (funkcja V)
	void Chopstick::signal()
	{
		std::lock_guard<decltype(m)> lock(m);
		++value;
		cv.notify_all(); // idk czy w tym przypadku to jest jakas wielka roznica czy jest _one czy _all
	}

	// funkcje do testowania czy wszystko dziala
	void Chopstick::printValue()
	{
		std::cout << value << std::endl;
	}

	void Chopstick::setValue(int val)
	{
		value = val;
	}