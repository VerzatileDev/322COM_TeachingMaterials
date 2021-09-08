// MThread.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <thread>

static const int num_threads = 10;

void call_from_thread() {
	  std::cout << "Hello from thread" << std::endl;
}

int main()
{
	//Launch a thread
	std::thread t1(call_from_thread);
	//Join the thread with the main thread
	t1.join();

	getchar();

	std::thread t[num_threads];
	//Launch a group of threads
	for (int i = 0; i < num_threads; ++i) {
	         t[i] = std::thread(call_from_thread);
	}
	std::cout << "Launched from the main\n";
	//Join the threads with the main thread
	for (int i = 0; i < num_threads; ++i) {
		  t[i].join();
	}

	getchar();
    return 0;
}

