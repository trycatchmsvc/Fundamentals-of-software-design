#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <map>
#include <vector>
#include <sstream>
#include <memory>


class ObjectManager {
private:
	std::vector<Object> objects;

public:
	size_t count() const;

	void parse_all_objects(std::vector<std::string>& vector_string) {
		for (const auto& item : vector_string)
		{
			if (parse_format1(item) != nullptr) {
				this->objects.push_back(*parse_format1(item));
			}
			else {
				this->objects.push_back(*parse_format2(item));
			}
		}
	};

	std::unique_ptr<Object> parse_format1(const std::string& str) {
		std::regex rgx(R"(\s*\"([a-zA-Z]+)\"\s*([\d.]+)\s*([\d.]+))");
		std::smatch match;
		if (std::regex_search(str, match, rgx)) {
			return std::make_unique<Object>(match[1].str(), match[2].str(), match[3].str());
		}
		else {
			return nullptr;
		}
	}

	std::unique_ptr<Object> parse_format2(const std::string& str) {
		std::regex rgx(R"(\s*([\d.]+)\s*([\d.]+)\s*\"([a-zA-Z]+)\")");
		std::smatch match;
		if (std::regex_search(str, match, rgx)) {
			return std::make_unique<Object>(match[3].str(), match[1].str(), match[2].str());
		}
		else {
			return nullptr;
		}
	}

	static std::vector<std::string> get_filters() {
		std::vector<std::string> filters; std::string color, enter_colors;
		std::cout << "Enter colors: ";
		std::getline(std::cin, enter_colors);
		std::stringstream ss(enter_colors);
		while (ss >> color) {
			filters.push_back(to_lower(color));
		}
		return filters;
	}

	static void print_object(std::vector<Object>& object_vector) {
		std::vector<std::string> color_filters = get_filters();

		for (Object& object : object_vector) {
			if (std::find(color_filters.begin(), color_filters.end(), object.get_color()) != color_filters.end()) {
				std::cout << object << std::endl;

			}
		}
	}

};

enum Color :int {
	red = 0,
	green,
	blue,
	value
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
	{Color::value, "value"}
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
	Object() { // Дефолтный конструктор
		this->color = Color::value;
		this->position.pos_x = 0;
		this->position.pos_y = 0;
	}

	Object(std::string _color, std::string _pos_x, std::string _pos_y) { // Дополнительный конструктор
		this->color = ColorMap.at(_color);
		this->position.pos_x = std::stof(_pos_x);
		this->position.pos_y = std::stof(_pos_y);
	};

	std::string get_color() { //Геттер
		return ReverseColorMap.at(color);
	}


	friend std::ostream& operator<<(std::ostream& os, const Object& obj); //Дружественная функция переопределения оператора 
};

std::ostream& operator<<(std::ostream& os, const Object& obj) {
	os << "Color: " << ReverseColorMap.at(obj.color) <<
		"\tpos_x: " << obj.position.pos_x << "\tpos_y: " << obj.position.pos_y << "\n";
	return os;
}

std::string to_lower(std::string _str) {
	for (char& c : _str) c = std::tolower(c);
	return _str;
}

std::vector<std::string> read_file(const std::string& file_name) {
	std::vector<std::string> file_lines;
	std::ifstream fin(file_name);
	if (fin.is_open() != true) { return file_lines; }; // Проверяем открылся ли поток, иначе возвращаем пустой вектор
	for (std::string line; std::getline(fin, line); ) {
		if (!line.empty()) {
			file_lines.push_back(to_lower(line));
		}
	}
	return file_lines;
}

int main() {
	std::vector <std::string> vector;
	vector = read_file("test.txt");
	
	

	return 0;
}