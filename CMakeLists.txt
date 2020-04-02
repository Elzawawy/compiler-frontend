cmake_minimum_required(VERSION 3.10)
project(LEXGEN)

set(CMAKE_CXX_STANDARD 17)


add_executable(LEXGEN language_parser.cpp language_parser.h nfa_state.cpp nfa_state.h dfa_state.cpp dfa_state.h dfa.cpp dfa.h nfa.cpp nfa.h token.cpp token.h regular_expression.cpp regular_expression.h utils.h partition.cpp partition.h lexical_analyzer_driver.cpp lexical_analyzer_driver.h tests/tests_main.cpp tests/lexical_analyzer_driver_test.cpp tests/catch.h)
