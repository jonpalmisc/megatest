cmake_minimum_required(VERSION 3.13)

project(megatest)

# Get the current Git commit hash to embed in the binary
execute_process(COMMAND git log -1 --format=%h
  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
  OUTPUT_VARIABLE GIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE)

add_executable(megatest megatest.c)
target_compile_features(megatest PRIVATE c_std_99)
target_compile_definitions(megatest PRIVATE MT_COMMIT="${GIT_HASH}")

if(MSVC)
  target_compile_options(megatest PRIVATE /W4)
else()
  target_compile_options(megatest PRIVATE -Wall -Wextra -fno-inline)
endif()
