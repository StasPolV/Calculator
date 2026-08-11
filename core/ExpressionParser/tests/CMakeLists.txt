add_executable(
  ExpressionParserTests test_expression_calculator.cpp test_evaluator.cpp
                        test_parser.cpp test_tokenizer.cpp)

target_link_libraries(ExpressionParserTests PRIVATE ExpressionParser
                                                    GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(ExpressionParserTests)
