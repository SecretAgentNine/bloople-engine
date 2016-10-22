// framework.h
// Provides a wrapper for the underlying systems (SDL and tinyXML)

#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <map>

#include "keycodes.h"

//----------

struct box {
	int x, y, w, h;
};

struct point {
	int x, y;
};

//----------

class framework;

//----------
//**********
//----------

//SDL_Texture wrapper class

class sprite {
friend class framework;
protected:
	SDL_Texture *texture;

public:
	sprite();
	sprite(SDL_Texture *t);
	~sprite();
	bool get_attributes(int *w, int *h);
	point location;
	box mask;
};

//----------
//**********
//----------

class framework {
protected:
	bool running;
	
	SDL_Renderer *renderer;
	SDL_Window *window;
	
public:
	framework() : renderer(NULL), window(NULL) {}
	~framework() {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window); 
		IMG_Quit();		
		SDL_Quit();
		std::cout << "framework exited successfully\n"; 
	}
	bool init();
	sprite* load_sprite(const char* filename);
	void render(std::vector<sprite*> *sprites);	
};

#endif
