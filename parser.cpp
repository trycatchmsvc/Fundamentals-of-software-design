#include "projects_types.h"
#include <regex>
#include <algorithm>
#include <memory>


auto ObjectParser::parse_object(const std::string& _string) -> std::unique_ptr<Object> {
    auto obj1 = parse_format2(_string);
    if (obj1) {
        return obj1;
    }
    
    obj1 = parse_format1(_string);
    if (obj1) {
        return obj1;
    }
    
    return parse_format3(_string);
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
	return nullptr;
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
	return nullptr;
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
	return nullptr;
}

std::string ObjectParser::to_lower(std::string& _str) {
    std::transform(_str.begin(), _str.end(), _str.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return _str;
}