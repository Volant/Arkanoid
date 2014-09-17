#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "util.h"

#include <string>

using namespace std;

class Image {

public:
	int bpp;

private:
	int file_size;
	int compression_method;
	unsigned int image_size;

	unsigned char* image_data;
	unsigned short* color_table;

public:
	GLuint texture;

	int width;
	int height;

	Image ();
	~Image ();

	int  load_BMP   (string);
	void load_image (string);
	void draw_image (int, int);

	void generate_texture ();
};

#endif
