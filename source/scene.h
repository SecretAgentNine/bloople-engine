#ifndef SCENE_H_
#define SCENE_H_

#include "framework.h"
#include "message.h"
#include <iostream>

//----------

class scene {
protected:
	logic_message msg_buffer;
	Uint32 prevtime;
	Uint32 now;
	int fps, frametime;

public:
	scene(framework* fwk, int frames_per_second) : fps(frames_per_second) {
		frametime = (int) ((1/((float) fps)) * 1000);	
	}
	virtual ~scene() { }
	virtual logic_message update() = 0;
	virtual void handle_message(message *msg) = 0;
};

//----------

class generic_scene: public scene {
private:
	bool quit;
	sprite* fence_sprite = nullptr;

public:
	generic_scene(framework* fwk, int frames_per_second);
	~generic_scene();
	logic_message update();
	void handle_message(message *msg);
};

#endif
