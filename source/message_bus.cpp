#include "message_bus.h"

message_bus::message_bus() : running(true) {
	flag_mapping = {
	{DRAW, subsystem::draw_flag},
	{RENDER, subsystem::render_flag},
	{INPUT, subsystem::input_flag}};
}

void message_bus::attach_system(subsystem* sys) {
	systems.push_back(sys);
}

//----------

message_bus::~message_bus() {
	running = false;

	//empty anything left in the message queue
	while (!message_queue.empty()) {
		delete message_queue.front();
		message_queue.pop_front();
	}
	std::cout << "message bus signing off\n";
}

//----------

void message_bus::post_message(message *msg) {
	message_queue.push_back(msg);
}

//----------

void message_bus::post_immediate_message(message *msg) {
	message_queue.push_front(msg);
}

//----------

void message_bus::update() {
	while (!message_queue.empty()) {
		message *msg = message_queue.front();
		char flag;

		//set the flags for the message we're sending
		if (msg->type == QUIT) {
			std::cout << "exiting!\n";
			running = false;
			break;
		}
		else { flag = flag_mapping[msg->type]; }


		//send the messages off to be handled by the threads
		for (sysiterator = systems.begin(); sysiterator != systems.end(); sysiterator++) {
			if (((*sysiterator)->get_flags() & flag) == flag) {
				(*sysiterator)->handle_message(msg);
			}
		}
		delete msg;
		message_queue.pop_front();
	}
	//update all the subsystems that need updating
	for (sysiterator = systems.begin(); sysiterator != systems.end(); sysiterator++) {
		if (((*sysiterator)->get_flags() & subsystem::update_flag) == subsystem::update_flag) {
			(*sysiterator)->update();
		}
	}
} 
