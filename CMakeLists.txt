cmake_minimum_required(VERSION 3.10)
project(Compiler)

set(CMAKE_CXX_STANDARD 17)

file(GLOB LEXGEN_SOURCE lexgen/*.cpp lexgen/*.h)
file(GLOB PRSGEN_SOURCE prsgen/*.cpp prsgen/*.h)
add_executable(LEXGEN lexgen/tests/whole_pipeline_tests.cpp tests_main.cpp catch.h utils.h ${LEXGEN_SOURCE})
add_executable(PRSGEN utils.h ${PRSGEN_SOURCE} ${LEXGEN_SOURCE})
