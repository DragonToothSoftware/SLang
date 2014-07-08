cmake_minimum_required(VERSION 2.6)
project(SLang)

include_directories(include)
include_directories(src)

add_definitions(-std=c++11)
add_definitions(-Wfatal-errors)

file(GLOB SOURCES "include/*.hpp" "src/*.cpp")

#find_package(CURSES)
#if(CURSES_FOUND)
#    include_directories(${SFML_INCLUDE_DIR})
#    link_directories(${SFML_ROOT}/lib)
#else()
#    message(FATAL_ERROR "SFML not found by find_package. Try specifying SFML_ROOT")
#endif()

add_executable(build/slang ${SOURCES})
