add_library(CalculatorController
    CalculatorController.cpp
    CalculatorController.h
)

target_include_directories(CalculatorController PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(CalculatorController
    PUBLIC
        CalculatorModel
        CalculatorWidget
        Qt6::Core
)
