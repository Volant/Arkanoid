#include "util.h"
#include "image.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define BITMAPCOREHEADER 12
#define OS22XBITMAPHEADER 64
#define BITMAPINFOHEADER 40
#define BITMAPV2INFOHEADER 52
#define BITMAPV3INFOHEADER 56
#define BITMAPV4HEADER 108
#define	BITMAPV5HEADER 124

using namespace std;

Image::Image () {
}

Image::~Image () {
	free (this->image_data);
}

int Image::load_BMP (string file_name) {
	FILE *f;

	if (f = fopen (file_name.c_str(), "r")) {

		// Reading BMP header
		unsigned char header[14];
		fread (header, 14, 1, f);

		int data_offset = (int (header[13]) << 24) + (int (header[12]) << 16) + (int (header[11]) << 8) + int (header[10]);
		this->file_size = (int (header[5]) << 24) + (int (header[4]) << 16) + (int (header[3]) << 8) + int (header[2]);

		// Reading DIB header
		fread (header, 4, 1, f);
		int dib_header_size = (int (header[3]) << 24) + (int (header[2]) << 16) + (int (header[1]) << 8) + int (header[0]);

		unsigned int color_table_size = 0;

		unsigned char *dib_header;
		dib_header = (unsigned char *) malloc (dib_header_size);
		switch (dib_header_size) {
			case BITMAPINFOHEADER:
				fread (dib_header, dib_header_size, 1, f);
				this->width = (int (dib_header[3]) << 24) + (int (dib_header[2]) << 16) + (int (dib_header[1]) << 8) + int (dib_header[0]);
				this->height = (int (dib_header[7]) << 24) + (int (dib_header[6]) << 16) + (int (dib_header[5]) << 8) + int (dib_header[4]);
				this->bpp = (int (dib_header[11]) << 8) + int (dib_header[10]);
				this->compression_method = (int (dib_header[15]) << 24) + (int (dib_header[14]) << 16) + (int (dib_header[13]) << 8) + int (dib_header[12]);
				this->image_size = (int (dib_header[19]) << 24) + (int (dib_header[18]) << 16) + (int (dib_header[17]) << 8) + int (dib_header[16]);
				color_table_size = (int (dib_header[35]) << 24) + (int (dib_header[34]) << 16) + (int (dib_header[33]) << 8) + int (dib_header[32]);
				break;
		}
		free (dib_header);

		float t = this->bpp / 8.0;
		t *= this->width;
		unsigned long row_size = int (t + int (t) % 4);
		unsigned long mem_allocated = this->width * 7 * this->height;

		this->image_data = (unsigned char *) malloc (mem_allocated);

		if (this->image_data == NULL) {
			printf ("Memory is not allocated\n");
			exit (1);
		}

		unsigned char* row = (unsigned char *) malloc (row_size);

		unsigned long offset = 0;

		fseek (f, data_offset, SEEK_SET);
		for (int j = 0; j < this->height; j++) {
			if (feof (f)) break;

			int n = fread (row, 1, row_size, f);
			if (n < row_size) break;

			for (unsigned long i = 0; i < row_size; i++) {
				unsigned int a, b;
				a = (row[i] & 0xF0) >> 4;
				b =  row[i] & 0x0F;


				// color table was read manually. will not implemented in code 
				// in nearest future because I plan to use PNG images
				if (color_table_size > 0) {
					switch (a) {
						case 0:
							a = 0xFF0000;
						case 1:
							a = 0x9DFF9A;
							break;
						case 2:
							a = 0x57FF54;
							break;
						case 3:
							a = 0x11B90E;
							break;
					}

					switch (b) {
						case 1:
							b = 0x9DFF9A;
							break;
						case 2:
							b = 0x57FF54;
							break;
						case 3:
							b = 0x11B90E;
							break;
					}

				}

				if (4 == this->bpp) {

					if (row_size - i < ( int (t) % 4 + 1 )) break;

					this->image_data[offset] = a & 0xFF;
					this->image_data[offset+1] = (a >> 8) & 0xFF;
					this->image_data[offset+2] = a >> 16; 
					offset += 3;

					this->image_data[offset] = b & 0xFF;
					this->image_data[offset+1] = (b >> 8) & 0xFF;
					this->image_data[offset+2] = b >> 16;
					offset += 3;

				}

				if (24 == this->bpp) {

					this->image_data[offset]   = row[i];
					this->image_data[offset+1] = row[i+1];
					this->image_data[offset+2] = row[i+2];

					offset += 3;
					i+=2;

					if (row_size - i <= 3) break;
				}
			}
		}

		free (row);
	}
}


void Image::generate_texture () {
	glEnable(GL_TEXTURE_2D);

	// allocate a texture ID
	glGenTextures(1, &texture);

	// select our texture as current
	glBindTexture(GL_TEXTURE_2D, texture);

	if (this->bpp == 4) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, this->image_data);
	} else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_BGR, GL_UNSIGNED_BYTE, this->image_data);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glDisable(GL_TEXTURE_2D);
}

void Image::draw_image (int x, int y) {
	glEnable(GL_TEXTURE_2D);
	glColor3d(1,1,1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//_MIPMAP_LINEAR);


	glBindTexture(GL_TEXTURE_2D, texture);

	x = texture * 100;
	int coeff = 1;

	glBegin(GL_QUADS);
	    glTexCoord2d(1,0); glVertex2d (x + this->width * coeff, x + this->height * coeff);
	    glTexCoord2d(0,0); glVertex2d (x,                   	x + this->height * coeff);
	    glTexCoord2d(0,1); glVertex2d (x,                   	x);
	    glTexCoord2d(1,1); glVertex2d (x + this->width * coeff, x);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void Image::load_image (string file_name) {
	FILE *f;

	if (f = fopen (file_name.c_str(), "r")) {

		// Reading BMP header
		unsigned char header[14];
		fread (header, 14, 1, f);
		if (header[0] == 'B' and header[1] == 'M') {
			this->load_BMP (file_name);
		} else {
			printf ("Unknown file format\n");
		}

#if USE_VIDEO_MODE == 1
		this->generate_texture ();
		this->draw_image (100, 100);
#endif 

		fclose (f);
	} else {
		printf ("Some error %d\n", errno);
	}
}
