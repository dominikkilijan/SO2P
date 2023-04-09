#include "Chopstick.h"
#include <mutex>
#include <condition_variable>
#include <iostream>

std::mutex m;
std::condition_variable cv;


	void Chopstick::wait()
	{
		std::unique_lock<decltype(m)> lock(m);
		while (!value)
			cv.wait(lock);
		--value;
		//std::cout << value << std::endl;
	}

	void Chopstick::signal()
	{
		std::lock_guard<decltype(m)> lock(m);
		++value;
		cv.notify_one();
		//std::cout << value << std::endl;
	}

	void Chopstick::printValue()
	{
		std::cout << value << std::endl;
	}

	void Chopstick::setValue(int val)
	{
		value = val;
	}