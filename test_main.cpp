#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>
#include "projects_types.h"
#include "project_types.cpp"
#include "parser.cpp"

#include <sstream>
#include <memory>


BOOST_AUTO_TEST_SUITE(TestObjectParser)

BOOST_AUTO_TEST_CASE(Parse_Format1_Ok)
{
    ObjectParser parser;
    std::string input = "\"red\" 10 20";

    auto obj = parser.parse_object(input);

    BOOST_REQUIRE(obj != nullptr);
    BOOST_CHECK_EQUAL(obj->get_color(), "red");
}

BOOST_AUTO_TEST_CASE(Parse_Format1_InvalidColor)
{
    ObjectParser parser;
    std::string input = "\"pink\" 10 20";

    auto obj = parser.parse_object(input);

    BOOST_CHECK(obj == nullptr);
}

BOOST_AUTO_TEST_CASE(Parse_Format2_Ok)
{
    ObjectParser parser;
    std::string input = "10 \"red\" 20";

    auto obj = parser.parse_object(input);

    BOOST_REQUIRE(obj != nullptr);
    BOOST_CHECK_EQUAL(obj->get_color(), "red");
}

BOOST_AUTO_TEST_CASE(Parse_Format2_InvalidColor)
{
    ObjectParser parser;
    std::string input = "10 \"pink\" 20";

    auto obj = parser.parse_object(input);

    BOOST_CHECK(obj == nullptr);
}

BOOST_AUTO_TEST_CASE(Parse_Format3_Ok)
{
    ObjectParser parser;
    std::string input = "10 20 \"green\"";

    auto obj = parser.parse_object(input);

    BOOST_REQUIRE(obj != nullptr);
    BOOST_CHECK_EQUAL(obj->get_color(), "green");
}

BOOST_AUTO_TEST_CASE(Parse_Format3_InvalidColor)
{
    ObjectParser parser;
    std::string input = "10 20 \"pink\"";

    auto obj = parser.parse_object(input);

    BOOST_CHECK(obj == nullptr);
}

BOOST_AUTO_TEST_CASE(Parse_Filter_OK)
{
    ObjectParser parser;
    std::string input = "10 20 \"pink\"";

    auto obj = parser.parse_object(input);

    BOOST_CHECK(obj == nullptr);
}

BOOST_AUTO_TEST_CASE(Object_Constructor_InvalidColor) {
    BOOST_CHECK_THROW(Object("invalid", "1", "2"), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()

