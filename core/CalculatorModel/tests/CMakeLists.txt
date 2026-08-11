add_executable(CalculatorModelTests test_calculator_model.cpp)

target_link_libraries(CalculatorModelTests PRIVATE CalculatorModel
                                                   GTest::gtest_main Qt6::Core)

include(GoogleTest)
gtest_discover_tests(CalculatorModelTests)
