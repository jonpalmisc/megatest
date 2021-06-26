cmake_minimum_required(VERSION 3.0)

project(megatest)

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fno-inline")

add_executable(megatest megatest.c)
target_compile_features(megatest PRIVATE c_std_99)
target_compile_options(megatest PRIVATE -Wall -Wextra)
