project(libunfo)

cmake_minimum_required (VERSION 2.6)
include (${CMAKE_ROOT}/Modules/CheckFunctionExists.cmake)
include (${CMAKE_SOURCE_DIR}/version.cmake)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --pedantic --std=c99 -Wall -Wextra -O2 -fno-strict-aliasing -g")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -gdb -O0")

set(VERSION "${libunfo.VERSION_MAJOR}.${libunfo.VERSION_MINOR}.${libunfo.VERSION_PATCH}")

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_BINARY_DIR}/src")

add_subdirectory(src)
add_subdirectory(tests)
