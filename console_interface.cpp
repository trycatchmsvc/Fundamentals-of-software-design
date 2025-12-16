#include "projects_types.h"
#include <iostream>
#include <sstream>
#include <algorithm>

std::vector<std::string> ConsoleInterface::get_filters() {
	std::vector<std::string> filters;
	std::string color;
	std::string enter_colors;
	std::cout << "Enter colors: ";
	std::getline(std::cin, enter_colors);
	std::stringstream stream(enter_colors);
	while (stream >> color) {
		filters.push_back(ObjectParser::to_lower(color));
	}
	return filters;
}

void ConsoleInterface::print_object(const std::vector<std::string>& color_filters, std::vector<Object>& objects) {
	for (Object& object : objects)
	{
		if (std::find(color_filters.begin(), color_filters.end(), object.get_color()) != color_filters.end())
		{
			std::cout << object << '\n';
		}
	}
}