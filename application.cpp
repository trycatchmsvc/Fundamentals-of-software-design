#include "projects_types.h"
#include <iostream>
#include <sstream>
#include <algorithm>

void Application::run(const std::vector<std::string>& vector_file) {
	std::vector<std::string> color_filter = ConsoleInterface::get_filters();
	for (const std::string & line : vector_file) {
		manager.addObject(parser.parse_object(line));
	}
	ui.print_object(color_filter, manager.objects);
}