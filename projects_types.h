#pragma once
#include <string>
#include <memory>
#include <vector>
#include <ostream>
#include <map>

enum Color :uint8_t;
extern const std::map<std::string, Color> ColorMap;
extern const std::map <Color, std::string> ReverseColorMap;

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
    Object();
    Object(const std::string & _color, const std::string & _pos_x, const std::string & _pos_y);
    std::string get_color();
    friend std::ostream& operator<<(std::ostream& os, const Object& obj);
};

class ObjectManager {
private:
    std::vector<Object> objects;
public:
    void addObject(std::unique_ptr<Object> obj);
    friend class Application;
};

class ObjectParser {
public:
    std::unique_ptr<Object> parse_object(const std::string& _string);
    static std::string to_lower(std::string& _str);
private:
    std::unique_ptr<Object> parse_format1(const std::string& str);
    std::unique_ptr<Object> parse_format2(const std::string& str);
    std::unique_ptr<Object> parse_format3(const std::string& str);
};

class ConsoleInterface {
public:
    static std::vector<std::string> get_filters();
    static void print_object(const std::vector<std::string>& color_filters, std::vector<Object>& objects);
};

class Application {
private:
    ObjectManager manager;
    ObjectParser parser;
    ConsoleInterface ui;
public:
    void run(const std::vector<std::string> & vector_file);
};
