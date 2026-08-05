add_library(ExpressionParser 
				Tokenizer.cpp Parser.cpp Evaluator.cpp
				Tokenizer.h Parser.h Evaluator.h ExpressionCalculator.h ExpressionError.h)

target_include_directories(ExpressionParser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if (BUILD_TESTING)
	add_subdirectory(tests)
endif()
