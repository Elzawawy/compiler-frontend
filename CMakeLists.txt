cmake_minimum_required(VERSION 3.10)
project(LEXGEN)

set(CMAKE_CXX_STANDARD 17)



add_executable(PRSGEN main.cpp prsgen/grammar_parser.cpp prsgen/grammar_parser.h prsgen/parsing_table_generator.cpp prsgen/parsing_table_generator.h prsgen/predictive_parser.cpp prsgen/predictive_parser.h prsgen/non_terminal.cpp prsgen/non_terminal.h)