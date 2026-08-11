add_library(CalculatorModel CalculatorModel.cpp CalculatorModel.h)

target_link_libraries(CalculatorModel PUBLIC ExpressionParser Qt6::Core)
target_include_directories(CalculatorModel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
