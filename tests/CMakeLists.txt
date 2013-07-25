find_library(CHECK_LIBRARY NAMES check)

include_directories(${CHECK_INCLUDE_DIR})

set (objlist_test_SRC objlist_test.c)
set (objlist_test_HEAD objlist_test.h)

add_executable(test_objlist ${objlist_test_SRC})

target_link_libraries(test_objlist unfo)
target_link_libraries(test_objlist ${CHECK_LIBRARY})
set_target_properties(test_objlist PROPERTIES COMPILE_FLAGS "${CMAKE_C_FLAGS} -g")

