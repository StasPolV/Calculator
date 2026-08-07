cmake_minimum_required(VERSION 3.28)

project(Calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

option(BUILD_TESTING "Build unit tests" ON)

if (BUILD_TESTING)
    enable_testing()
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

add_subdirectory(core/ExpressionParser)
add_subdirectory(core/CalculatorModel)
add_subdirectory(core/SettingsModel)
add_subdirectory(gui)
add_subdirectory(controller)

qt_add_executable(Calculator core/main.cpp resources/resources.qrc)

target_link_libraries(Calculator PRIVATE
    controllers
    Qt6::Core
    Qt6::Widgets
)
