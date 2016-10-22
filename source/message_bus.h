#ifndef MESSAGEBUS_H
#define MESSAGEBUS_H

#include <queue>
#include <deque>
#include <mutex>
#include <atomic>
#include <thread>
#include <iostream>

#include "message.h"
#include "components.h"

class subsystem;

//----------

struct relay {
	message msg;
	subsystem* sys;
};

//----------
//**********
//----------

class message_bus {
private:
	std::deque<message*> message_queue;
	
	std::vector<subsystem*> systems;
	std::vector<subsystem*>::iterator sysiterator;

	//manage multithreaded resources
	std::mutex deque_mutex;
	
	//threadpool!
	int num_threads;
	std::vector<std::thread*> threads;
	void thread_loop();

	//communicate with threads
	std::mutex relay_mutex;
	std::queue<relay*> relay_queue;

	//stuff for synchronizing threads
	std::atomic<bool> synch;
	std::atomic<int> synch_count;
	void synchronize_threads();
			
public:
	std::atomic<bool> running;

	message_bus(int num_threads);
	~message_bus();
	void attach_system(subsystem* sys);
	void post_message(message *msg);
	void post_immediate_message(message *msg);
	void update();
};

#endif
