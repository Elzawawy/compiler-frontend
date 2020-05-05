cmake_minimum_required(VERSION 3.10)
project(Compiler)

set(CMAKE_CXX_STANDARD 17)
file(GLOB LEXGEN_SOURCE lexgen/*.cpp lexgen/*.h)
file(GLOB PRSGEN_SOURCE prsgen/*.cpp prsgen/*.h)
add_executable(LEXGEN catch.h utils.h ${LEXGEN_SOURCE})
add_executable(PRSGEN catch.h utils.h ${PRSGEN_SOURCE} ${LEXGEN_SOURCE})