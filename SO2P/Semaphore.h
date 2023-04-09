#pragma once
#include <mutex>
#include <condition_variable>
#include <iostream>

class Semaphore
{
	//std::mutex mutex_;
	//std::condition_variable condition_;
	//unsigned long count_ = 1; // Initialized as unlocked.
public:
	void release();
	void acquire();
	void printCount();
};

