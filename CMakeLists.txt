cmake_minimum_required(VERSION 3.20)
project(ip_filter)

set(CMAKE_CXX_STANDARD 20)

add_executable(ip_filter src/ip_filter.cpp src/main.cpp include/ip_filter.h)
