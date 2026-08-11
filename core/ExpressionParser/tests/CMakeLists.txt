add_executable(ExpressionParserTests test_expression_calculator.cpp)

target_link_libraries(ExpressionParserTests PRIVATE ExpressionParser
                                                    GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(ExpressionParserTests)
