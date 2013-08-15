find_library(CHECK_LIBRARY NAMES check)

include_directories(${CHECK_INCLUDE_DIR})

set(test_files updateinfo1.xml.gz update-short.xml.gz)

set (doc_test_SRC doc_test.c)
set (doc_test_HEAD doc_test.h)

set (objlist_test_SRC objlist_test.c)
set (objlist_test_HEAD objlist_test.h)

set (log_test_SRC log_test.c)
set (log_test_HEAD log_test.h)

set (parse_test_SRC parse_test.c)
set (parse_test_HEAD "")

add_executable(test_objlist ${objlist_test_SRC})
add_executable(test_doc ${doc_test_SRC})
add_executable(test_log ${log_test_SRC})
add_executable(test_parse ${parse_test_SRC})

target_link_libraries(test_objlist unfo)
target_link_libraries(test_objlist ${CHECK_LIBRARY})
set_target_properties(test_objlist PROPERTIES COMPILE_FLAGS "${CMAKE_C_FLAGS} -g")

target_link_libraries(test_doc unfo)
target_link_libraries(test_doc ${CHECK_LIBRARY})
set_target_properties(test_doc PROPERTIES COMPILE_FLAGS "${CMAKE_C_FLAGS} -g")

target_link_libraries(test_log unfo)
target_link_libraries(test_log ${CHECK_LIBRARY})
set_target_properties(test_log PROPERTIES COMPILE_FLAGS "${CMAKE_C_FLAGS} -g")

foreach(file ${test_files})
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${file} DESTINATION ./)
endforeach()

target_link_libraries(test_parse unfo)
target_link_libraries(test_parse ${CHECK_LIBRARY})
set_target_properties(test_parse PROPERTIES COMPILE_FLAGS "${CMAKE_C_FLAGS} -g")
