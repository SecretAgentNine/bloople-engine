#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>

#include "framework.h"
#include "message_bus.h"
#include "message.h"
#include "keycodes.h"
#include "scene.h"

//----------
//**********
//----------

class subsystem {
protected:
	framework *fwk;
	message_bus *bus;

	bool running = true;

	char flags;
	
public:
	static const char draw_flag   = 0b00000001;		//flags to receive various message types
	static const char render_flag = 0b00000010;
	static const char input_flag  = 0b00000100;
	static const char update_flag = 0b10000000;

	subsystem(framework *f, message_bus *m);
	virtual void handle_message(message *msg) {}
	virtual void update() {}
	char get_flags() { return flags; }
};

//----------
//**********
//----------

class render_system : public subsystem {
protected:
	std::vector<sprite*> draw_list;

public:
	render_system(framework *f, message_bus *m) : subsystem(f,m) { flags = subsystem::draw_flag | subsystem::render_flag; }
	void handle_message(message *msg);
};

//----------
//**********
//----------

class input_system : public subsystem {
protected:
	std::map<SDL_Keycode, keycode> keymapping {		//mapping SDL keycodes onto the custom keycodes
	{SDLK_0, KEY_0},															//(I really hope this doesn't switch from SDL input because I really don't want to rewrite this table)
	{SDLK_1, KEY_1},
	{SDLK_2, KEY_2},
	{SDLK_3, KEY_3},
	{SDLK_4, KEY_4},
	{SDLK_5, KEY_5},
	{SDLK_6, KEY_6},
	{SDLK_7, KEY_7},
	{SDLK_8, KEY_8},
	{SDLK_9, KEY_9},
	{SDLK_LALT, KEY_ALT},
	{SDLK_BACKSLASH, KEY_BACKSLASH},
	{SDLK_BACKSPACE, KEY_BACKSPACE},
	{SDLK_CAPSLOCK, KEY_CAPSLOCK},
	{SDLK_LEFTBRACKET, KEY_OPENBRACKET},
	{SDLK_RIGHTBRACKET, KEY_CLOSEBRACKET},
	{SDLK_COMMA, KEY_COMMA},
	{SDLK_LCTRL, KEY_CONTROL},
	{SDLK_PLUS, KEY_ADD},
	{SDLK_MINUS, KEY_DASH},
	{SDLK_PERIOD, KEY_PERIOD},
	{SDLK_DELETE, KEY_DELETE},
	{SDLK_SLASH, KEY_SLASH},
	{SDLK_DOWN, KEY_DOWN},
	{SDLK_END, KEY_END},
	{SDLK_RETURN, KEY_ENTER},
	{SDLK_EQUALS, KEY_EQUALS},
	{SDLK_ESCAPE, KEY_ESCAPE},
	{SDLK_F1, KEY_F1},
	{SDLK_F2, KEY_F2},
	{SDLK_F3, KEY_F3},
	{SDLK_F4, KEY_F4},
	{SDLK_F5, KEY_F5},
	{SDLK_F6, KEY_F6},
	{SDLK_F7, KEY_F7},
	{SDLK_F8, KEY_F8},
	{SDLK_F9, KEY_F9},
	{SDLK_F10, KEY_F10},
	{SDLK_F11, KEY_F11},
	{SDLK_F12, KEY_F12},
	{SDLK_HOME, KEY_HOME},
	{SDLK_INSERT, KEY_INSERT},
	{SDLK_LEFT, KEY_LEFT},
	{SDLK_LGUI, KEY_LEFTMETA},
	{SDLK_RGUI, KEY_RIGHTMETA},
	{SDLK_NUMLOCKCLEAR, KEY_NUMLOCK},
	{SDLK_KP_0, KEY_NUMPAD_0},
	{SDLK_KP_1, KEY_NUMPAD_1},
	{SDLK_KP_2, KEY_NUMPAD_2},
	{SDLK_KP_3, KEY_NUMPAD_3},
	{SDLK_KP_4, KEY_NUMPAD_4},
	{SDLK_KP_5, KEY_NUMPAD_5},
	{SDLK_KP_6, KEY_NUMPAD_6},
	{SDLK_KP_7, KEY_NUMPAD_7},
	{SDLK_KP_8, KEY_NUMPAD_8},
	{SDLK_KP_9, KEY_NUMPAD_9},
	{SDLK_PAGEDOWN, KEY_PAGEDOWN},
	{SDLK_PAGEUP, KEY_PAGEUP},
	{SDLK_RIGHT, KEY_RIGHT},
	{SDLK_SCROLLLOCK, KEY_SCROLLLOCK},
	{SDLK_SEMICOLON, KEY_SEMICOLON},
	{SDLK_LSHIFT, KEY_LEFTSHIFT},
	{SDLK_RSHIFT, KEY_RIGHTSHIFT},
	{SDLK_QUOTE, KEY_QUOTE},
	{SDLK_SPACE, KEY_SPACE},
	{SDLK_TAB, KEY_TAB},
	{SDLK_UP, KEY_UP},
	{SDLK_a, KEY_a},
	{SDLK_b, KEY_b},
	{SDLK_c, KEY_c},
	{SDLK_d, KEY_d},
	{SDLK_e, KEY_e},
	{SDLK_f, KEY_f},
	{SDLK_g, KEY_g},
	{SDLK_h, KEY_h},
	{SDLK_i, KEY_i},
	{SDLK_j, KEY_j},
	{SDLK_k, KEY_k},
	{SDLK_l, KEY_l},
	{SDLK_m, KEY_m},
	{SDLK_n, KEY_n},
	{SDLK_o, KEY_o},
	{SDLK_p, KEY_p},
	{SDLK_q, KEY_q},
	{SDLK_r, KEY_r},
	{SDLK_s, KEY_s},
	{SDLK_t, KEY_t},
	{SDLK_u, KEY_u},
	{SDLK_v, KEY_v},
	{SDLK_w, KEY_w},
	{SDLK_x, KEY_x},
	{SDLK_y, KEY_y},
	{SDLK_z, KEY_z}};

public:
	input_system(framework *f, message_bus *m) : subsystem(f,m) { flags = subsystem::update_flag; }
	void update();
};

//----------
//**********
//----------

class game_logic : public subsystem {
protected:
	scene* current_scene = nullptr;
	scene* default_scene = nullptr;
	logic_message msg_buffer;

public:
	game_logic(framework *f, message_bus *m);
	~game_logic();
	void handle_message( message *msg );
	void update();
	void load_scene(scene* _scene);
};

#endif
