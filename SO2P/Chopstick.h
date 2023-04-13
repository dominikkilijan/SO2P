#pragma once

class Chopstick
{
private:
	// Na start chopstick jest dostepny do uzycia
	int value = 1;

public:
	void wait();
	void signal();
	void printValue();
	void setValue(int val);
};

