#ifndef __BAT_H__
#define __BAT_H__

#include "image.hpp"

#define SPEED 5

class Bat {
private:
	int __x, __y;
	Image texture;

public:
	Bat ();
	~Bat ();

	Image* image();

	unsigned x () { return __x; };
	unsigned y () { return __y; };

	void move_left  () { if (__x > SPEED) __x -= SPEED; }
	void move_right () { if (__x < SCREEN_WIDTH - SPEED - texture.width) __x += SPEED; }
};

#endif
