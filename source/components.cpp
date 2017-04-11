#include "components.h"

subsystem::subsystem(framework *f, message_bus *m) : fwk(f), bus(m) { bus->attach_system(this); }

//----------
//**********
//----------

void render_system::handle_message (message *msg) {
	switch (msg->type)	 {
		case DRAW:
			draw_list.push_back(msg->draw.sp);	//add a sprite to the draw list
			break;
		case RENDER:							//render and erase the draw_list
			fwk->render(&draw_list);
			draw_list.erase(draw_list.cbegin(), draw_list.cend());
			break;
	}
}

//----------
//**********
//----------

void input_system::update() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			message *msg = new message;
			msg->type = QUIT;
			bus->post_immediate_message(msg);
		}
		else if (event.type == SDL_KEYDOWN) {
			message *msg = new message;
			msg->type = INPUT;
			msg->input.type = KEYDOWN;
			msg->input.keydown.key = keymapping[event.key.keysym.sym];
			bus->post_message(msg);
		}
	}
}

//----------
//**********
//----------

audio_system::audio_system(framework *fwk, message_bus *bus) : subsystem(fwk, bus) {
	flags = subsystem::audio_flag | subsystem::update_flag;
}

//----------

void audio_system::handle_message(message *msg) {
	//do a thing
}
		
	
	
