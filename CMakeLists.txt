cmake_minimum_required(VERSION 3.15)
project(TicTacToe)

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -std=c++17 -fconstexpr-depth=2048")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -std=c++17 -DNDEBUG")

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(TicTacToe
        src/Main.cpp
        src/Search.h
        src/Board.h
        src/Defs.h
        src/StackVector.h)
