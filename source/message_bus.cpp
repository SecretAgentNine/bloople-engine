#include "message_bus.h"

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
