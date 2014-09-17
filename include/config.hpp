#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "util.h"
#include "image.hpp"

#include <stdio.h>
#include <yaml-cpp/yaml.h>

#include <string>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

struct Level {
	string* lines;
	unsigned lines_count;
};

class Config {

private:
	std::map < unsigned, Level > levels;
	unsigned levels_count;

	std::map < unsigned, Image > images;
	unsigned images_count;

public:
	Config ();
	~Config ();

	unsigned lines_count (unsigned);
	unsigned sprites_count (unsigned);
	string* lines (unsigned);
	std::map < unsigned, Image > sprites ();

};

#endif
