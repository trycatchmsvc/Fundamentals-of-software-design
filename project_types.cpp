#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <map>
#include <vector>
#include <sstream>
#include <memory>
#include "projects_types.h"



enum Color :int {
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


Object::Object() { // Дефолтный конструктор
	this->color = Color::value;
	this->position.pos_x = 0;
	this->position.pos_y = 0;
}


	

Object::Object(std::string _color, std::string _pos_x, std::string _pos_y) { // Дополнительный конструктор
	try {
		this->color = ColorMap.at(_color);
	}
	catch (const std::out_of_range& ex) {
		throw;
	}

	this->position.pos_x = std::stof(_pos_x);
	this->position.pos_y = std::stof(_pos_y);
};

std::string Object::get_color() { //Геттер
	return ReverseColorMap.at(color);
}




std::ostream& operator<<(std::ostream& os, const Object& obj) { // Перегрузка оператора вывода в поток
	os << "Color: " << ReverseColorMap.at(obj.color) <<
		"\tpos_x: " << obj.position.pos_x << "\tpos_y: " << obj.position.pos_y << "\n";
	return os;
}



size_t ObjectManager::count() {
	return objects.size();
}

void ObjectManager::addObject(std::unique_ptr<Object> obj) {
	if (obj.get() != nullptr) {
		objects.push_back(std::move(*obj));
	}
}




std::unique_ptr<Object> ObjectParser::parse_object(const std::string& _string) {
	auto obj1 = parse_format1(_string);
	if (obj1 != nullptr)
	{
		return obj1;
	}
	else if ((obj1 = parse_format1(_string)) != nullptr)
	{
		return obj1;
	}
	else {
		return parse_format3(_string);
	}


};

std::string ObjectParser::to_lower(std::string& _str) {
	for (char& c : _str) c = std::tolower(c);
	return _str;
}



std::unique_ptr<Object> ObjectParser::parse_format1(const std::string& str) {
	std::regex rgx(R"(^\s*\"([a-zA-Z]+)\"\s*(\d+(?:\.\d+)?)\s*(\d+(?:\.\d+)?)\s*$)");
	std::smatch match;
	if (std::regex_search(str, match, rgx)) {
		if (ColorMap.find(match[1].str()) == ColorMap.end()) {
			return nullptr;
		}
		return std::make_unique<Object>(match[1].str(), match[2].str(), match[3].str());
	}
	else {
		return nullptr;
	}
}

std::unique_ptr<Object> ObjectParser::parse_format2(const std::string& str) {
	std::regex rgx(R"(\s*(\d+(?:\.\d+)?)\s*(\d+(?:\.\d+)?)\s*\"([a-zA-Z]+)\")");
	std::smatch match;
	if (std::regex_search(str, match, rgx)) {
		if (ColorMap.find(match[3].str()) == ColorMap.end()) {
			return nullptr;
		}
		return std::make_unique<Object>(match[3].str(), match[1].str(), match[2].str());
	}
	else {
		return nullptr;
	}
}

std::unique_ptr<Object> ObjectParser::parse_format3(const std::string& str) {
	std::regex rgx(R"(\s*(\d+(?:\.\d+)?)\s*"([a-zA-Z]+)\"\s*(\d+(?:\.\d+)?)\s*$)");
	std::smatch match;
	if (std::regex_search(str, match, rgx)) {
		if (ColorMap.find(match[2].str()) == ColorMap.end()) {
			return nullptr;
		}
		return std::make_unique<Object>(match[2].str(), match[1].str(), match[3].str());
	}
	else {
		return nullptr;
	}
}



std::vector<std::string> ConsoleInterface::get_filters() {
	std::vector<std::string> filters; std::string color, enter_colors;
	std::cout << "Enter colors: ";
	std::getline(std::cin, enter_colors);
	std::stringstream ss(enter_colors);
	while (ss >> color) {
		filters.push_back(ObjectParser::to_lower(color));
	}
	return filters;
}

void ConsoleInterface::print_object(const std::vector<std::string>& color_filters, std::vector<Object>& objects) {
	for (Object& object : objects)
	{
		if (std::find(color_filters.begin(), color_filters.end(), object.get_color()) != color_filters.end())
		{
			std::cout << object << std::endl;
		}
	}
}



void Application::run(const std::vector<std::string>& vector_file) {
	std::vector<std::string> color_filter = ui.get_filters();
	for (const std::string line : vector_file) {
		manager.addObject(parser.parse_object(line));
	}
	ui.print_object(color_filter, manager.objects);
}

