#ifndef MESSAGEBUS_H
#define MESSAGEBUS_H

#include <deque>
#include <iostream>
#include <map>

#include "message.h"
#include "components.h"

class subsystem;

//----------
//**********
//----------

class message_bus {
private:
	std::deque<message*> message_queue;
	
	std::vector<subsystem*> systems;
	std::vector<subsystem*>::iterator sysiterator;

	std::map<message_type, char> flag_mapping;
			
public:
	bool running;

	message_bus();
	~message_bus();
	void attach_system(subsystem* sys);
	void post_message(message *msg);
	void post_immediate_message(message *msg);
	void update();
};

#endif
