find_library(CHECK_LIBRARY NAMES check)

include_directories(${CHECK_INCLUDE_DIR})

set (doc_test_SRC doc_test.c)
set (doc_test_HEAD doc_test.h)

set (objlist_test_SRC objlist_test.c)
set (objlist_test_HEAD objlist_test.h)

add_executable(test_objlist ${objlist_test_SRC})
add_executable(test_doc ${doc_test_SRC})

target_link_libraries(test_objlist unfo)
target_link_libraries(test_objlist ${CHECK_LIBRARY})
set_target_properties(test_objlist PROPERTIES COMPILE_FLAGS "${CMAKE_C_FLAGS} -g")

target_link_libraries(test_doc unfo)
target_link_libraries(test_doc ${CHECK_LIBRARY})
set_target_properties(test_doc PROPERTIES COMPILE_FLAGS "${CMAKE_C_FLAGS} -g")
