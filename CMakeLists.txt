cmake_minimum_required( VERSION 3.0 FATAL_ERROR )
project( sudoku C CXX )

# Warn when somebody sneezes, treat warnings as errors, use modern C++
if( MSVC )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX /D_SCL_SECURE_NO_WARNINGS /std:c++14" )
else()
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -std=c++14" )
endif()

add_subdirectory( sudoku )
