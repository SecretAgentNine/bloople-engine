#include "components.h"

//----------

void render_system::handle_message (message *msg) {
	switch (msg->type)	 {
		case DRAW:
			draw_list.push_back(msg->draw.sp);
			break;
		case RENDER:
			fwk->render(&draw_list);
			draw_list.erase(draw_list.cbegin(), draw_list.cend());
			break;
	}
}

//----------
//**********
//----------

void input_system::get_events() {
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
		
	
	
