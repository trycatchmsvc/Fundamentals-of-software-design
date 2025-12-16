#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>
#include <regex>
#include <map>
#include <vector>
#include <sstream>
#include <memory>
#include "projects_types.h"

enum Color :uint8_t  {
	red = 0,
	green,
	blue,
	value
};

const std::map<std::string, Color> ColorMap = {
	{"red",Color::red},
	{"green",Color::green},
	{"blue", Color::blue},
};
const std::map <Color, std::string> ReverseColorMap = {
	{Color::red, "red"},
	{Color::green, "green"},
	{Color::blue, "blue"},
	{Color::value, "value"}
};


Object::Object() { //Default constructor
	this->color = Color::value;
	this->position.pos_x = 0;
	this->position.pos_y = 0;
}


Object::Object(const std::string & _color, const std::string & _pos_x, const std::string & _pos_y) { // Constructor
	try {
		this->color = ColorMap.at(_color);
	}
	catch (const std::out_of_range& ex) {
		throw;
	}

	this->position.pos_x = std::stof(_pos_x);
	this->position.pos_y = std::stof(_pos_y);
};

auto Object::get_color() -> std::string
 { //Getter
	return ReverseColorMap.at(color);
 }


std::ostream& operator<<(std::ostream& output_stream, const Object& obj) { // Friend function for COUT
	output_stream << "Color: " << ReverseColorMap.at(obj.color) <<
		"\tpos_x: " << obj.position.pos_x << "\tpos_y: " << obj.position.pos_y << "\n";
	return output_stream;
}


void ObjectManager::addObject(std::unique_ptr<Object> obj) {
	if (obj) {
		objects.push_back(*obj);
	}
}




