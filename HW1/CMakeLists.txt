cmake_minimum_required(VERSION 3.20)
project(HW1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)


add_executable(HW1 main.cpp ${UnitTest_src_regular} ${UnitTest_src_Posix})

