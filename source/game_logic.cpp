#include "components.h"

//----------

game_logic::game_logic(framework* f, message_bus* m, int fps) : subsystem(f,m), fps(fps) { 
	flags = subsystem::input_flag | subsystem::update_flag;
	//std::cout << "makin' a scene\n";
	default_scene = new generic_scene(fwk, fps);

	load_scene(default_scene);
}

//----------

game_logic::~game_logic() {
	std::cout << "cya!\n";
	delete default_scene;
}

//----------

void game_logic::handle_message( message *msg ) {
	current_scene->handle_message(msg);
}

//----------

void game_logic::update () {
	msg_buffer = current_scene->update();
	//std::cout << "msg_buffer length: " << msg_buffer.messages.size() << std::endl;
	for (std::vector<message*>::iterator iterator = msg_buffer.messages.begin(); iterator != msg_buffer.messages.end(); iterator++) {
		if ((*iterator)->type == QUIT) { bus->post_immediate_message(*iterator); }
		else { bus->post_message(*iterator); }
	}
}

//----------

void game_logic::load_scene(scene* _scene) {
	current_scene = _scene;
}


