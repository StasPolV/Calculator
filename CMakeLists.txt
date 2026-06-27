cmake_minimum_required(VERSION 3.16)

project(Calculator VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES src/main.cpp src/Calculator.cpp src/Calculator.h src/CalculatorWidget.cpp src/CalculatorWidget.h)

add_executable(Calculator ${PROJECT_SOURCES})

target_link_libraries(Calculator PRIVATE Qt6::Core Qt6::Widgets)

if(WIN32)
    set_target_properties(Calculator PROPERTIES WIN32_EXECUTABLE ON)
endif()
