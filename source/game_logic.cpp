#include "components.h"

//----------

game_logic::game_logic() : subsystem(f,m) { 
	flags = subsystem::input_flag | subsystem::update_flag;
	s = fwk->load_sprite("resources/fence.png");
	s->location.x = 0;
	s->location.y = 0;
	s->mask.x = 0;
	s->mask.y = 0;
	s->mask.w = -1;
	s->mask.h = -1;

	int w, h;
	s->get_attributes(&w, &h);
	std::cout << w << ", " << h << "\n";
}

//----------

game_logic::~game_logic() {
	delete s;
}

//----------

void game_logic::handle_message( message *msg ) {
	switch (msg->type) {
	case INPUT:
		switch (msg->input.type) {
		case KEYDOWN:
			switch (msg->input.keydown.key) {
			case KEY_UP:
			{
				s->location.y -=1;
				break;
			}
			case KEY_DOWN:
			{
				s->location.y +=1;
				break;
			}
			case KEY_LEFT:
			{
				s->location.x -= 1;
				break;
			}
			case KEY_RIGHT:
			{
				s->location.x += 1;
				break;
			}
			case KEY_ESCAPE:
			{
				message *m = new message;
				m->type = QUIT;
				bus->post_message(m);
				break;
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

//----------

void game_logic::update () {
	message *msg = new message;
	msg->type = DRAW;
	msg->draw.sp = s;
	bus->post_message(msg);

	msg = new message;	
	msg->type = RENDER;
	bus->post_message(msg);
}

