cmake_minimum_required(VERSION 3.16)

project(FundamentalsOfSoftwareDesign
        VERSION 1.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(app
    main.cpp
    project_types.cpp
    parser.cpp
    console_interface.cpp
    application.cpp
)

target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_options(app PRIVATE -Wall -Wextra -Wpedantic)