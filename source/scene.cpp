#include "scene.h"

generic_scene::generic_scene(framework* fwk, int frames_per_second) : scene(fwk, frames_per_second) {
	fence_sprite = fwk->load_sprite("resources/fence.png", 10, 10);
	fence_sprite->set_alpha(127);
	quit = false;
	prevtime = get_millis();
}

//----------

generic_scene::~generic_scene() {
	delete fence_sprite;
}

//----------

logic_message generic_scene::update() {
	now = get_millis();

	//limit the framerate
	if (now - prevtime < frametime) {
		delay_millis(frametime-now+prevtime);
	}
	prevtime = get_millis();

	msg_buffer.messages.clear();

	if (quit) {		//quit immediately
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
