#define CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "projects_types.h"


auto read_file(const std::string& file_name) -> std::vector<std::string> { // Read lines
	std::vector<std::string> file_lines;
	std::ifstream fin(file_name);
	if (!fin.is_open()) { return file_lines; }; // Check a stream, another return null vector
	for (std::string line; std::getline(fin, line); ) {
		if (!line.empty()) {
			file_lines.push_back(ObjectParser::to_lower(line));
		}
	}
	return file_lines;
}

auto main() -> int {
	std::vector <std::string> vector;
	vector = read_file("test.txt");
	


	Application app;
	app.run(vector);
	return 0;
}
