project(libunfo)

cmake_minimum_required (VERSION 2.6)
include (${CMAKE_ROOT}/Modules/CheckFunctionExists.cmake)
include (${CMAKE_SOURCE_DIR}/version.cmake)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --pedantic --std=c99 -Wall -Wextra -O2 -fno-strict-aliasing -g")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -gdb -O0")

set(VERSION "${libunfo.VERSION_MAJOR}.${libunfo.VERSION_MINOR}.${libunfo.VERSION_PATCH}")

set(ZLIB_SUPPORT YES)

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_BINARY_DIR}/src")

find_package(LibXml2 REQUIRED)
message("xml2dirs ${LIBXML2_INCLUDE_DIR}")
include_directories(${LIBXML2_INCLUDE_DIR})

add_custom_target(ctest DEPENDS test_parse_run test_doc_run)
add_custom_target(pytest DEPENDS test_py_run)
add_custom_target(test DEPENDS ctest pytest)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(docs EXCLUDE_FROM_ALL)
