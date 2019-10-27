cmake_minimum_required(VERSION 3.14)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 17)

add_executable(TicTacToe src/Main.cpp src/Board.h src/Enums.h src/Search.h src/Rays.h src/StackVector.h)
