set(libunfo_SRC unfo.c unfo_doc.c unfo_docupdate.c unfo_objlist.c unfo_obj.c
                unfo_mm.c unfo_hslist.c unfo_dict.c unfo_docref.c unfo_docpkg.c
                unfo_doccoll.c unfo_packed.c unfo_log.c unfo_log_codes.c
                unfo_parse.c unfo_elems.c
                unfo_utils.c)
set(libunfo_HDRS h/unfo.h h/unfo_doc.h h/unfo_docupdate.h h/unfo_objlist.h h/unfo_obj.h
                 h/unfo_mm.h h/unfo_hslist.h h/unfo_dict.h h/unfo_docref.h h/unfo_docpkg.h
                 h/unfo_doccoll.h h/unfo_packed.h h/unfo_log.h h/unfo_log_codes.h
                 h/unfo_parse.h h/unfo_types.h h/unfo_elems.h
                 h/unfo_utils.h)

find_library(EXPAT_LIBRARY NAMES expat)
find_package(EXPAT REQUIRED)
include_directories(${EXPAT_INCLUDE_DIR})

find_package(LibXml2 REQUIRED)
include_directories(${LIBXML2_INCLUDE_DIR})


add_library(unfo SHARED ${libunfo_SRC})
target_link_libraries(unfo m)
target_link_libraries(unfo ${LIBXML2_LIBRARIES})
target_link_libraries(unfo ${EXPAT_LIBRARY})

set_target_properties(unfo PROPERTIES SOVERSION ${VERSION})

if (${ZLIB_SUPPORT} STREQUAL YES)
    find_library(ZLIB_LIBRARY NAMES zlib)
    find_package(ZLIB REQUIRED)
    include_directories(${ZLIB_INCLUDE_DIRS})
    message("--- Linking with zlib support")
    target_link_libraries(unfo ${ZLIB_LIBRARIES})
endif()

IF (CMAKE_SIZEOF_VOID_P MATCHES "8")
    SET (LIB_SUFFIX "64")
ENDIF (CMAKE_SIZEOF_VOID_P MATCHES "8")
set (LIB_INST_DIR ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX})

install(FILES ${libunfo_HDRS} DESTINATION include/libunfo)
install(TARGETS unfo LIBRARY DESTINATION ${LIB_INST_DIR})

add_subdirectory(python)
