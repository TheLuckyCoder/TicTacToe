cmake_minimum_required(VERSION 3.15)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(TicTacToe
        src/Main.cpp
        src/Search.h
        src/Board.h
        src/Defs.h)
