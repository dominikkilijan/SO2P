#pragma once

class Chopstick
{
private:
//	std::mutex m;
//	std::condition_variable cv;
	int value = 1;

public:
	void wait();
	void signal();
	void printValue();
	void setValue(int val);
};

