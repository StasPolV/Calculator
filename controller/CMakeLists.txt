add_library(controllers CalculatorController.cpp CalculatorController.h
                        SettingsController.cpp SettingsController.h)

target_include_directories(controllers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(controllers PUBLIC CalculatorModel SettingsModel gui
                                         Qt6::Core)
