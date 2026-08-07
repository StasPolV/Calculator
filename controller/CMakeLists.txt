add_library(CalculatorController
    CalculatorController.cpp
    CalculatorController.h
	SettingsController.cpp
	SettingsController.h
)

target_include_directories(CalculatorController PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(CalculatorController
    PUBLIC
        CalculatorModel
		SettingsModel
        gui
        Qt6::Core
)
