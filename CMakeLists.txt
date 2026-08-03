cmake_minimum_required(VERSION 3.28)

project(Calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

qt_add_executable(Calculator core/main.cpp)

target_link_libraries(Calculator PRIVATE Qt6::Core Qt6::Widgets)

add_subdirectory(core/ExpressionParser)
add_subdirectory(core/CalculatorModel)
