#include "message_bus.h"

void message_bus::thread_loop() {
	relay* r;
	while(running) {
		if (synch) {
			std::cout << "syn\n"; 
			synch_count++;
			while(synch) {} //wait until everyone else is synchronized
		}

		//if a message is waiting to be handled, grab it and go
		r = NULL;
		relay_mutex.lock();
		if (!relay_queue.empty()) {
			r = relay_queue.front();
			relay_queue.pop();
		}
		relay_mutex.unlock();
		if (r != NULL) {
			r->sys->handle_message(&(r->msg));
			delete r; //clean up!
		}
	}
}

//----------

void message_bus::synchronize_threads() {
	synch_count = 0;
	synch = true;
	while (synch_count < num_threads -1) {} //wait to be synchronized
	synch = false;
	std::cout << "-\n";
}

//----------

void message_bus::attach_system(subsystem* sys) {
	systems.push_back(sys);
}

//----------

message_bus::message_bus(int num_threads) : num_threads(num_threads), synch(false) {
	for (int i = 0; i < num_threads; i++) {
		threads.push_back( new std::thread(&message_bus::thread_loop, this) );
	}
}

//----------

message_bus::~message_bus() {
	//start shutting down threads
	running = false;

	//empty anything left in the message queue
	while (!message_queue.empty()) {
		delete message_queue.front();
		message_queue.pop_front();
	}
	//make sure the threads shut down before we do
	for (std::vector<std::thread*>::iterator i = threads.begin(); i != threads.end(); i++) {
		(*i)->join();
	}
	std::cout << "message bus signing off\n";
}

//----------

void message_bus::post_message(message *msg) {
	std::lock_guard<std::mutex> guard(deque_mutex);
	message_queue.push_back(msg);
}

//----------

void message_bus::post_immediate_message(message *msg) {
	std::lock_guard<std::mutex> guard(deque_mutex);
	message_queue.push_front(msg);
}

//----------

void message_bus::update() {
	while (!message_queue.empty()) {
		message *msg = message_queue.front();
		char flag;

		//set the flags for the message we're sending
		switch (msg->type) {
		case DRAW:
			flag = subsystem::draw_flag;
			break;
		case RENDER:
			flag = subsystem::render_flag;
			break;
		case INPUT:
			std::cout << "received key " << msg->input.keydown.key << "\n";
			flag = subsystem::input_flag;
			break;
		case QUIT:
			std::cout << "exiting!\n";
			running = false;
			break;
		}
		//send the messages off to be handled by the threads
		for (sysiterator = systems.begin(); sysiterator != systems.end(); sysiterator++) {
			if ((*sysiterator)->get_flags() & flag) {
				relay *r = new relay;
				r->sys = *sysiterator;
				r->msg = *msg;
				relay_mutex.lock();
				relay_queue.push(r);
				relay_mutex.unlock();
			}
		}
		
		delete msg;
		message_queue.pop_front();
	}
	//don't keep trying to handle messages while updating
	synchronize_threads();
} 
