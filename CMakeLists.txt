cmake_minimum_required(VERSION 3.27)
project(Plotter)

set(CMAKE_CXX_STANDARD 17)

add_executable(Plotter main.cpp olcPixelGameEngine.h)
target_link_libraries(Plotter X11  GL pthread png "stdc++fs")
