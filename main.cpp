#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <map>
#include <vector>
#include <sstream>
using std::cout;


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
		this->position.pos_x = std::stod(_pos_x);
		this->position.pos_y = std::stod(_pos_y);
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

std::vector<std::string> read_lines_from_file(const std::string& file_name); // Считывает строки с файла
std::vector<Object> parse_all_objects(std::vector<std::string>& vector_string); // Функция парсинга строк
std::string to_lower_string(const std::string& _str); // Перевод строки в нижний регистр
Object parse_format1(std::string std); // Регулярка на формат строки
Object parse_format2(std::string std); // Регулярка на формат строки
std::vector<std::string> get_filters(); // Возвращает вектор цветов для фильтра
static void print_object_vector(std::vector<Object>& object_vector); // Выводит обьекты исходя из фильтра
//static 


int main() {
	std::vector<Object> objects;
	std::vector <std::string> vector;
	vector = read_lines_from_file("test.txt");
	objects = parse_all_objects(vector);
	print_object_vector(objects);
	
	return 0;
}

std::vector<std::string> read_lines_from_file(const std::string &file_name) {
	std::vector<std::string> file_lines; 
	std::ifstream fin(file_name);
	if (fin.is_open() != true) { return file_lines; }; // Проверяем открылся ли поток, иначе возвращаем пустой вектор
	for (std::string line; std::getline(fin, line); ) {
		if (!line.empty()) {
			file_lines.push_back(line);
		}
	}
	return file_lines;
}

std::string to_lower_string(const std::string& _str) {
	std::string str = _str;
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

std::vector<Object> parse_all_objects(std::vector<std::string>& vector_string) {
	std::vector<Object> object_vector;
	for (int i{ 0 }; i < vector_string.size(); i++) {
		try {
			object_vector.push_back(parse_format1(vector_string[i]));
		}
		catch (std::out_of_range) {
			object_vector.push_back(parse_format2(vector_string[i]));
		}
	}

	return object_vector;
};

Object parse_format1(std::string str) {
	std::regex rgx(R"(\s*\"([a-zA-Z]+)\"\s*([\d.]+)\s*([\d.]+))");
	std::smatch match;
	std::regex_search(str, match, rgx);
	
	Object obj(match[1].str(), match[2].str(), match[3].str());

	return obj;
}

Object parse_format2(std::string str) {
	std::regex rgx(R"(\s*([\d.]+)\s*([\d.]+)\s*\"([a-zA-Z]+)\")");
	std::smatch match;
	std::regex_search(str, match, rgx);

	Object obj(match[3].str(), match[1].str(), match[2].str());

	return obj;
}

std::vector<std::string> get_filters() {
	std::vector<std::string> filters; std::string color, enter_colors;
	std::cout << "Enter colors: ";
	std::getline(std::cin, enter_colors);
	std::stringstream ss(enter_colors);
	while (ss >> color) {
		filters.push_back(color);
	}
	return filters;
}

static void print_object_vector(std::vector<Object> &object_vector) {

	std::vector<std::string> color_filters = get_filters();
	for (int i{ 0 }; i < object_vector.size(); i++) {
		for (std::string current_color : color_filters) {
			if (object_vector[i].get_color() == current_color) {
				std::cout << object_vector[i] << std::endl;
			}
		}
	}
}