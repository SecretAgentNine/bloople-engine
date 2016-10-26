#ifndef SCENE_H_
#define SCENE_H_

#include "message.h"
#include <iostream>
#include <queue>
#include <map>

//----------

class scene {
private:

public:
	scene() {}
	virtual void update();
	virtual void handle_message(message *msg);
};

//----------

class generic_scene: public scene {
public:
	generic_scene();
	void update();
	void handle_message(message *msg);
};

#endif
