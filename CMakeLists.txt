cmake_minimum_required(VERSION 2.6)
project(SLang)

include_directories(include)
include_directories(src)

add_definitions(-std=c++11)

set(SOURCES src/main.cpp src/lexer.cpp include/lexer.hpp)

add_executable(build/slang ${SOURCES})
