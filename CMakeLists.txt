cmake_minimum_required(VERSION 3.10)
project(LEXGEN)

set(CMAKE_CXX_STANDARD 17)

add_executable(LEXGEN main.cpp file_parser.cpp file_parser.h nfa_state.cpp nfa_state.h dfa_state.cpp dfa_state.h dfa.cpp dfa.h nfa.cpp nfa.h token.cpp token.h  partition.cpp partition.h )