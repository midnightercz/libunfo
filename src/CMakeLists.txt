set(libunfo_SRC unfo.c unfo_doc.c unfo_docupdate.c unfo_objlist.c unfo_obj.c
                unfo_mm.c unfo_hslist.c unfo_dict.c unfo_docref.c unfo_docpkg.c
                unfo_doccoll.c unfo_packed.c unfo_log.c unfo_log_codes.c
                unfo_parse.c unfo_elems.c
                unfo_utils.c)
set(libunfo_HEAD unfo.h unfo_doc.h unfo_docupdate.h unfo_objlist.h unfo_obj.h
                unfo_mm.h unfo_hslist.h unfo_dict.h unfo_docref.h unfo_docpkg.h
                unfo_doccoll.h unfo_packed.h unfo_log.h unfo_log_codes.h
                unfo_parse.h unfo_types.h unfo_elems.h
                unfo_utils.h)

find_library(EXPAT_LIBRARY NAMES expat)
find_package(EXPAT REQUIRED)
include_directories(${EXPAT_INCLUDE_DIR})

find_package(LibXml2 REQUIRED)
include_directories(${LIBXML2_INCLUDE_DIR})


add_library(unfo SHARED ${libunfo_SRC})
target_link_libraries(unfo m)
target_link_libraries(unfo ${LIBXML2_LIBRARIES})
target_link_libraries(unfo ${EXPAT_LIBRARY})

if (${ZLIB_SUPPORT} STREQUAL YES)
    find_library(ZLIB_LIBRARY NAMES zlib)
    find_package(ZLIB REQUIRED)
    include_directories(${ZLIB_INCLUDE_DIRS})
    message("--- Linking with zlib support")
    target_link_libraries(unfo ${ZLIB_LIBRARIES})
endif()


add_subdirectory(python)
