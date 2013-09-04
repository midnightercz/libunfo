if (python_version_required STREQUAL "3")
    find_package(PythonLibs 3)
    find_package(PythonInterp 3 REQUIRED)
else()
    find_package(PythonLibs 2.7)
    find_package(PythonInterp 2.7 REQUIRED)
endif()

execute_process (COMMAND ${PYTHON_EXECUTABLE} -c "from sys import stdout; from distutils import sysconfig; stdout.write(sysconfig.get_python_lib(True))" OUTPUT_VARIABLE PYTHON_INSTALL_DIR)

include_directories(${PYTHON_INCLUDE_PATH})
include_directories(${LIBUNFO_INCLUDE_PATH})
include_directories("${PROJECT_SOURCE_DIR}/src")

set(test_files test.py update-short.xml update-short1.xml.gz ../__init__.py)
foreach (file ${test_files})
    file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/tests/${file}" DESTINATION "./libunfo/")
endforeach(file ${test_files})


set(pyunfo_SRC pyunfo.c pyunfo_doc.c pyunfo_docupdate.c pyunfo_docref.c
               pyunfo_doccoll.c pyunfo_docpkg.c
               pyunfo_utils.c pyunfo_objlist.c
               pyunfo_objlist_iter.c)
set(pyunfo_HDR pyunfo.h pyunfo_doc.h pyunfo_docupdate.c pyunfo_docref.h
               pyunfo_doccoll.h pyunfo_docpkg.h
               pyunfo_utils.h pyunfo_objlist.h
               pyunfo_objlist_iter.h)

add_library(pyunfo SHARED ${pyunfo_SRC})
set_target_properties(pyunfo PROPERTIES LIBRARY_OUTPUT_DIRECTORY "./libunfo")
set_target_properties(pyunfo PROPERTIES PREFIX "")
set_target_properties(pyunfo PROPERTIES LIBRARY_OUTPUT_NAME "_libpyunfo")

target_link_libraries(pyunfo unfo)
target_link_libraries(pyunfo ${EXPAT_LIBRARIES})
target_link_libraries(pyunfo ${LIBXML2_LIBRARIES})
target_link_libraries(pyunfo ${PYTHON_LIBRARIES})

install(FILES __init__.py DESTINATION ${PYTHON_INSTALL_DIR}/libunfo)
install(TARGETS pyunfo LIBRARY DESTINATION ${PYTHON_INSTALL_DIR}/libunfo)
