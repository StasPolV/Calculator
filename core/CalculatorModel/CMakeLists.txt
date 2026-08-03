add_executable(CalculatorModel 
				CalculatorModel.cpp
                CalculatorModel.h)

target_include_directories(CalculatorModel PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../ExpressionParser)
