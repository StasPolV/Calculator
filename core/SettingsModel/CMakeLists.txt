add_library(SettingsModel SettingsModel.cpp SettingsModel.h)

target_link_libraries(SettingsModel PUBLIC Qt6::Core)
target_include_directories(SettingsModel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
