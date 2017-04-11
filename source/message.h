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

struct input_message {
	input_type type;
	union {
		key_down keydown;
		key_up keyup;
	};
};

//----------

//audio messages
typedef enum {
	PLAY,
	PAUSE,
	FADEIN,
	FADEOUT
} audio_type;

struct play_audio {
	sound* audio;
	int loops;
};

struct pause_audio {
	sound* audio;
};

struct fadein_audio {
	sound* audio;
	int loops;
	int milliseconds;
};

struct fadeout_audio {
	sound* audio;
	int milliseconds;
};

struct audio_message {
	audio_type type;
	union {
		play_audio play;
		pause_audio pause;
		fadein_audio fadein;
		fadeout_audio fadeout;
	};
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

struct message {
	message_type type;
	union {
		draw_message draw;
		render_message render;
		input_message input;
		audio_message audio;
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
