#ifndef __ARKANOID_H__
#define __ARKANOID_H__

#include "image.hpp"
#include "config.hpp"

class Arkanoid {

protected:
	Config* conf;

	bool is_done;

	unsigned current_level;

	SDL_Window *sdlWindow;

public:
	void game_loop ();
	void draw_level (unsigned);

	Arkanoid ();
	Arkanoid (SDL_Window*);
	~Arkanoid ();
};

#endif
