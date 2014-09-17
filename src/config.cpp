#include "config.hpp"

std::map < unsigned, Image > Config::sprites () {
	return images;
}

unsigned Config::lines_count (unsigned level) {
	return levels[level].lines_count;
}

string* Config::lines (unsigned level) {
	return levels[level].lines;
}

/*
void operator >> (const YAML::Node& node, std::string& line) {
	line = node.Scalar ();
}
*/

void operator >> (const YAML::Node& node, Level& level) {
	try {
		const YAML::Node& level_row = node["level"];
		level.lines_count = level_row.size();
		level.lines = new string[level.lines_count];
		for (unsigned i = 0; i < level.lines_count; i++) {
			level_row[i] >> level.lines[i];
		}
	} catch (YAML::ParserException& e) {
	}
}

void operator >> (const YAML::Node& node, std::map < unsigned, Image > & images) {
	try {
		const YAML::Node& sprite_row = node["sprites"];
		for (unsigned i = 0; i < sprite_row.size(); i++) {
			std::string sprite_path;
			sprite_row[i] >> sprite_path;
			images[images.size()].load_image (sprite_path);
		}
	} catch (YAML::ParserException& e) {
	}
}

Config::Config () {
	std::ifstream fin("../conf/arkanoid.conf");

	string title = "";

	YAML::Parser parser(fin);
	YAML::Node doc;

	parser.GetNextDocument(doc);

	for (unsigned i = 0; i < doc.size(); i++) {
		try {
			const YAML::Node& level_row = doc[i]["level"];
			levels_count = doc[i].size();
			doc[i] >> levels[levels.size()];
		} catch (YAML::KeyNotFound& e) {
		}

		try {
			const YAML::Node& images_row = doc[i]["sprites"];
			images_count = doc[i].size();
			doc[i] >> images;
		} catch (YAML::KeyNotFound& e) {
		}
	}
}

Config::~Config () {
	levels.clear();
	images.clear();
}
