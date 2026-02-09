cmake_minimum_required(VERSION 4.1)
project(produtor_consumidor)

set(CMAKE_CXX_STANDARD 20)

add_executable(produtor_consumidor main.cpp
        Buffer.cpp
        Buffer.h)
