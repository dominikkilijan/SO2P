#include "Chopstick.h"
#include <mutex>
#include <condition_variable>
#include <iostream>

std::mutex m;
std::condition_variable cv;
int value = 1;


	void Chopstick::wait()
	{
		std::unique_lock<decltype(m)> lock(m);
		while (!value)
			cv.wait(lock);
		--value;
	}

	void Chopstick::signal()
	{
		std::lock_guard<decltype(m)> lock(m);
		++value;
		cv.notify_one();
	}

	void Chopstick::printValue()
	{
		std::cout << value << std::endl;
	}