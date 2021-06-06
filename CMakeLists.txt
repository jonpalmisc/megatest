cmake_minimum_required(VERSION 3.0)

project(megetest)

add_executable(megatest megatest.c)
target_compile_features(megatest PRIVATE c_std_99)
target_compile_options(megatest PRIVATE -Wall -Wextra)
