cmake_minimum_required(VERSION 3.10)
project(Compiler)

set(CMAKE_CXX_STANDARD 17)


add_executable(LEXGEN lexgen/language_parser.cpp lexgen/language_parser.h lexgen/nfa_state.cpp lexgen/nfa_state.h lexgen/dfa_state.cpp lexgen/dfa_state.h lexgen/dfa.cpp lexgen/dfa.h lexgen/nfa.cpp lexgen/nfa.h lexgen/token.cpp lexgen/token.h lexgen/regular_expression.cpp lexgen/regular_expression.h utils.h lexgen/partition.cpp lexgen/partition.h lexgen/min_dfa.cpp lexgen/min_dfa.h lexgen/lexical_analyzer_driver.cpp lexgen/lexical_analyzer_driver.h tests_main.cpp lexgen/tests/lexical_analyzer_driver_test.cpp catch.h lexgen/tests/whole_pipeline_tests.cpp lexgen/min_dfa.h)
add_executable(PRSGEN prsgen/main.cpp prsgen/grammar_parser.cpp prsgen/grammar_parser.h prsgen/parsing_table_generator.cpp prsgen/parsing_table_generator.h prsgen/predictive_parser.cpp prsgen/predictive_parser.h prsgen/non_terminal.cpp prsgen/non_terminal.h)
