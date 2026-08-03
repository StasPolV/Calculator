add_library(CalculatorWidget CalculatorWidget.h CalculatorWidget.cpp)

target_include_directories(CalculatorWidget PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(CalculatorWidget PUBLIC Qt6::Core Qt6::Widgets)
