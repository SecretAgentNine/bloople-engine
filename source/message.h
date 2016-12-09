#ifndef MESSAGE_H
#define MESSAGE_H

#include "framework.h"
#include "keycodes.h"
#include <vector>

//input messages
typedef enum {
	KEYDOWN,
	KEYUP
} input_type;

struct key_down {
	keycode key;
};

struct key_up {
	keycode key;
};


//----------

typedef enum {
	DRAW,
	RENDER,
	INPUT,
	AUDIO,
	QUIT } message_type;

struct draw_message {
	sprite *sp;
};

struct render_message {
	int num;
};

struct input_message {
	input_type type;
	union {
		key_down keydown;
		key_up keyup;
	};
};

/*struct audio_message {
	audio_type type;
	union {
		//stuff
	};
}; //*/

struct message {
	message_type type;
	union {
		draw_message draw;
		render_message render;
		input_message input;
	};
};

//----------
//structs for loading scene resources

typedef enum {
	NONE,
	MENU,
	EXIT
} logic_option;

struct logic_message {
	std::vector<message*> messages;
	logic_option option;
};

//----------

class message_bus;

#endif
