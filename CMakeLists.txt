cmake_minimum_required(VERSION 4.1)
project(produtor_consumidor)

add_executable(produtor_consumidor main.cpp
        Buffer.cpp
        Buffer.h)
target_compile_features(produtor_consumidor PRIVATE cxx_std_20)