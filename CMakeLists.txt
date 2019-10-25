cmake_minimum_required(VERSION 3.15)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 17)

add_executable(TicTacToe main.cpp src/Board.cpp src/Board.h src/Enums.h src/Search.cpp src/Search.h src/Rays.h src/StackVector.h)