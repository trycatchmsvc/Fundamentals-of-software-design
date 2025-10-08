#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <map>
#include <vector>
using std::cout;


enum Color :int {
	red = 0,
	green,
	blue
};
static const std::map<std::string, Color> ColorMap = {
	{"red",Color::red},
	{"green",Color::green},
	{"blue", Color::blue},
};

static const std::map <Color, std::string> ReverseColorMap = {
	{Color::red, "red"},
	{Color::green, "green"},
	{Color::blue, "blue"},
};

class Point2D {
public:
	float pos_x;
	float pos_y;
};

class Object {
private:
	Color color;
	Point2D position;

public:
	std::string get_color() {
		return ReverseColorMap.at(color);
	}

	void parse_string(const std::string& str) {
		
		std::regex rgx1(R"(\s*\"([a-zA-Z]+)\"\s*([\d.]+)\s*([\d.]+))");  
		std::regex rgx2(R"(\s*([\d.]+)\s*([\d.]+)\s*\"([a-zA-Z]+)\")");

		std::smatch match;

		if (std::regex_search(str, match, rgx1)) {
			std::string str_color = match[1].str();
			std::transform(str_color.begin(), str_color.end(), str_color.begin(), ::tolower);
			this->color = ColorMap.at(str_color);
			this->position.pos_x = stod(match[2].str());
			this->position.pos_y = stod(match[3].str());
		}
		else if (std::regex_search(str, match, rgx2)) {
			std::string str_color = match[3].str(); 
			std::transform(str_color.begin(), str_color.end(), str_color.begin(), ::tolower);
			this->color = ColorMap.at(str_color);
			this->position.pos_x = stod(match[1].str());  
			this->position.pos_y = stod(match[2].str());  
		}
		else {
			std::cout << "Can't parse: " << str << std::endl;
		}
	}

	friend std::ostream& operator<<(std::ostream& os, const Object& obj);
};

std::ostream& operator<<(std::ostream& os, const Object& obj) {
	os << "Color: " << ReverseColorMap.at(obj.color) <<
		"\tpos_x: " << obj.position.pos_x << "\tpos_y: " << obj.position.pos_y << "\n";
	return os;
}


int main() {
	std::string color_filters;
	std::cout << "Enter color filter (use space for list): ";
	std::getline(std::cin, color_filters);

	std::ifstream fin;
	fin.open("test.txt");

	std::vector<Object> objects;

	for (std::string line; std::getline(fin, line); ) {
		if (!line.empty()) {
			Object obj;
			obj.parse_string(line);
			objects.push_back(obj);
		}
	}

	for (int i = 0; i < objects.size(); i++) {
		std::string current_color;
		for (char c : color_filters) {
			if (c == ' ') {
				if (!current_color.empty() && objects[i].get_color() == current_color) {
					std::cout << objects[i] << std::endl;
					break;
				}
				current_color.clear();
			}
			else {
				current_color += c;
			}
		}
		if (!current_color.empty() && objects[i].get_color() == current_color) {
			std::cout << objects[i] << std::endl;
		}
	}

	return 0;
}
