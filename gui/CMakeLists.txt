add_library(gui
    CalculatorWidget.h CalculatorWidget.cpp
    DisplayWidget.h DisplayWidget.cpp
    KeypadWidget.h KeypadWidget.cpp
    TopBarWidget.h TopBarWidget.cpp
    SettingsWidget.h SettingsWidget.cpp
    ScalableIconButton.h ScalableIconButton.cpp
)

target_include_directories(gui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(gui PUBLIC Qt6::Core Qt6::Widgets)
