#include "scene.h"

using us = std::chrono::microseconds;
using sclock = std::chrono::steady_clock;

generic_scene::generic_scene(framework* fwk) : scene(fwk) {
	fence_sprite = fwk->load_sprite("resources/fence.png", 10, 10);
	quit = false;
	//prevtime = sclock::now();
}

//----------

logic_message generic_scene::update() {
	//std::cout << "time since previous loop: " << std::chrono::duration_cast<us>(sclock::now()-prevtime).count() << " us\n";
	//prevtime = sclock::now();
	msg_buffer.messages.clear();

	if (quit) {
		message *msg = new message;
		msg->type = QUIT;
		msg_buffer.messages.push_back(msg);
		return msg_buffer;
	}

	message *msg = new message;
	msg->type = DRAW;
	msg->draw.sp = fence_sprite;
	msg_buffer.messages.push_back(msg);

	msg = new message;	
	msg->type = RENDER;
	msg_buffer.messages.push_back(msg);
	
	msg_buffer.option = NONE;
	return msg_buffer;
}

//----------

void generic_scene::handle_message(message* msg) {
switch (msg->type) {
	case INPUT:
		switch (msg->input.type) {
		case KEYDOWN:
			switch (msg->input.keydown.key) {
			case KEY_UP:
			{
				fence_sprite->location.y -=1;
				break;
			}
			case KEY_DOWN:
			{
				fence_sprite->location.y +=1;
				break;
			}
			case KEY_LEFT:
			{
				fence_sprite->location.x -= 1;
				break;
			}
			case KEY_RIGHT:
			{
				fence_sprite->location.x += 1;
				break;
			}
			case KEY_ESCAPE:
			{
				quit = true;
			}
			default: { break; }
			}
			break;
		default: { break; }
		}
	default:
		break;
	}
}


