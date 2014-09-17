#include "util.h"
#include "bat.hpp"

Image* Bat::image () {
	return &texture;
}

Bat::Bat () {
	__x = 200;
	__y = 280;

	texture.load_image ("../img/bat.bmp");
}

Bat::~Bat () {

}
