cmake_minimum_required(VERSION 2.6)
project(SLang)

include_directories(include)
include_directories(src)

add_definitions(-std=c++11)
add_definitions(-Wfatal-errors)

file(GLOB SOURCES "include/*.hpp" "src/*.cpp")

if(NOT DEFINED WIN32)
    find_library(TERMCAP_LIBRARY termcap)
ENDIF()

add_executable(slang ${SOURCES})

if(NOT DEFINED WIN32)
    target_link_libraries(slang ${TERMCAP_LIBRARY})
ENDIF()
