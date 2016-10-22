#include "framework.h"

bool framework::init() {
	//initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cerr << "error: failed to initialize SDL! (" << SDL_GetError() << ")\n";
		return false; 
	}

	//create the window and renderer
	window = SDL_CreateWindow("Winona", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
					400,
					400,
					SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//abort if there were errors
	if (window == NULL || renderer == NULL) {
		std::cerr << "error: failed to open window\n";
		return false;
	}

	//configure the renderer
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
	SDL_RenderSetLogicalSize(renderer, 400, 400);

	SDL_SetRenderDrawColor(renderer, 0,0,0,255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	//initialize SDL_image
	int img_flags = IMG_INIT_PNG;
	if( IMG_Init(img_flags)&img_flags != img_flags) {
		std::cerr << "error: could not initialize SDL_image! (" << IMG_GetError() << ")\n";
		return false;
	}

	//initialize SDL_mixer	
	int mix_flags = MIX_INIT_MP3|MIX_INIT_OGG;
	if( Mix_Init(mix_flags)&mix_flags != mix_flags ) {
		std::cerr << "error: could not initalize SDL_mixer! (" << Mix_GetError() << ")\n";
		return false;
	}

	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
		std::cerr << "error: could not initalize SDL_mixer! (" << Mix_GetError() << ")\n";
		return false;
	}

	running = true;
	SDL_ShowCursor(0);

	return true;
}

sprite* framework::load_sprite(const char* filename) {
	SDL_Surface *tmp = NULL;
	SDL_Texture *tex = NULL;
	
	//load image and convert to texture
	tmp = IMG_Load(filename);
	tex = SDL_CreateTextureFromSurface(renderer, tmp);
	SDL_FreeSurface(tmp);

	//freak out if something went wrong
	if (tex == NULL) {
		std::cerr << "ERROR: Could not load file " << filename << ": " << SDL_GetError() << "\n";
		throw "BAD FILE";
	}
	sprite *s = new sprite(tex);
	return s;
}

//----------

void framework::render(std::vector<sprite*> *sprites) {
	//clear the screen
	SDL_RenderClear(renderer);

	//render each sprite in turn
	std::vector<sprite*>::iterator i = sprites->begin();
	SDL_Rect *maskrect, *destrect;
	for ( ; i != sprites->end(); i++) {
		destrect = new SDL_Rect;
		//if the width and height weren't set, render the whole thing
		if ((*i)->mask.w == -1 && (*i)->mask.h == -1) {
			maskrect = NULL;
			int width, height;
			(*i)->get_attributes(&width, &height);
			destrect->w = width;
			destrect->h = height;
		}
		//otherwise, render just the part specified
		else { 
 			maskrect = new SDL_Rect;
			maskrect->x = (*i)->mask.x;
			maskrect->y = (*i)->mask.y;
			maskrect->w = (*i)->mask.w;
			maskrect->h = (*i)->mask.h;

			destrect->w = (*i)->mask.w;
			destrect->h = (*i)->mask.h;
		}
		
		//set the location to render to
		destrect->x = (*i)->location.x;
		destrect->y = (*i)->location.y;
		//std::cout << "rendering at (" << destrect->x << "," << destrect->y << ")\n";

		//render and clean up
		SDL_RenderCopy(renderer, (*i)->texture, maskrect, destrect);
		delete maskrect;
		delete destrect;
	}
	//update the screen
	SDL_RenderPresent(renderer);
}	

//----------
//**********
//----------

sprite::sprite() {
	texture = NULL;
}

//----------

sprite::sprite(SDL_Texture *t) {
	texture = t;
}

//----------

bool sprite::get_attributes(int *w, int *h) {
	if (!SDL_QueryTexture(texture, NULL, NULL, w, h)) { return true; }
	else { return false; }
}

//----------

sprite::~sprite() {
	SDL_DestroyTexture(texture);
}
