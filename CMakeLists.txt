cmake_minimum_required(VERSION 2.6)
project(SLang)

include_directories(include)
include_directories(src)

add_definitions(-std=c++11)

file(GLOB SOURCES "include/*.hpp" "src/*.cpp")

add_executable(build/slang ${SOURCES})
