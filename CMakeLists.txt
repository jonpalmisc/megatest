cmake_minimum_required(VERSION 3.13)

project(megatest)

# Get the current Git commit hash to embed in the binary
execute_process(COMMAND git log -1 --format=%h
  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
  OUTPUT_VARIABLE GIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE)

set(MT_SOURCE src/megatest.c src/store.c src/store.h)

# Add Objective-C portions on macOS only
if(APPLE)
  list(APPEND MT_SOURCE src/extra_objc.h src/extra_objc.m)
endif()

add_executable(megatest ${MT_SOURCE})
target_compile_features(megatest PRIVATE c_std_99)
target_compile_definitions(megatest PRIVATE MT_COMMIT="${GIT_HASH}")

# Add Objective-C portions on macOS only
if(APPLE)
  target_link_libraries(megatest PRIVATE "-framework Foundation")
endif()

if(MSVC)
  target_compile_options(megatest PRIVATE /W4)
else()
  target_compile_options(megatest PRIVATE -Wall -Wextra -fno-inline)
endif()

add_custom_target(format WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  COMMAND clang-format -i --style=LLVM ${MT_SOURCE})
