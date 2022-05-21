cmake_minimum_required(VERSION 3.21)
project(dv C)

set(CMAKE_C_STANDARD 99)

add_executable(dv func.h node0.c node1.c node2.c node3.c prog3.c util.c)
