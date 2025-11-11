#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "projects_types.h"


std::vector<std::string> read_file(const std::string& file_name) { // Чтение строк
	std::vector<std::string> file_lines;
	std::ifstream fin(file_name);
	if (fin.is_open() != true) { return file_lines; }; // Проверяем открылся ли поток, иначе возвращаем пустой вектор
	for (std::string line; std::getline(fin, line); ) {
		if (!line.empty()) {
			file_lines.push_back(ObjectParser::to_lower(line));
		}
	}
	return file_lines;
}

int main() {
	std::vector <std::string> vector;
	vector = read_file("test.txt");
	


	Application app;
	app.run(vector);
	return 0;
}
