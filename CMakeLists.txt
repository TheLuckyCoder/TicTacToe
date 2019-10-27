cmake_minimum_required(VERSION 3.14)
project(TicTacToe)

set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_CXX_STANDARD 20)

add_executable(TicTacToe main.cpp src/Board.h src/Enums.h src/Search.h src/Rays.h src/StackVector.h)
