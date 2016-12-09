#ifndef SCENE_H_
#define SCENE_H_

#include "framework.h"
#include "message.h"
#include <iostream>
#include <chrono>

//----------

class scene {
protected:
	logic_message msg_buffer;
	//std::chrono::time_point<std::chrono::steady_clock> prevtime;

public:
	scene(framework* fwk) {}
	virtual logic_message update() = 0;
	virtual void handle_message(message *msg) = 0;
};

//----------

class generic_scene: public scene {
private:
	bool quit;
	sprite* fence_sprite = nullptr;

public:
	generic_scene(framework* fwk);
	logic_message update();
	void handle_message(message *msg);
};

#endif
