#ifndef MESSAGEBUS_H
#define MESSAGEBUS_H

#include <deque>
#include <iostream>

#include "message.h"
#include "components.h"

class subsystem;

//----------

struct relay {
	message* msg;
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
			
public:
	bool running;

	message_bus() : running(true) {}
	~message_bus();
	void attach_system(subsystem* sys);
	void post_message(message *msg);
	void post_immediate_message(message *msg);
	void update();
};

#endif
