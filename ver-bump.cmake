include (version.cmake)

if (BUMP STREQUAL "0")
    MATH( EXPR libunfo_RELEASE "${libunfo_RELEASE} +1")
elseif (BUMP STREQUAL "1")
    MATH( EXPR libunfo_VERSION_PATCH "${libunfo_VERSION_PATCH} +1")
    set (libunfo_RELEASE 1)
elseif (BUMP STREQUAL "2")
    MATH( EXPR libunfo_VERSION_MINOR "${libunfo_VERSION_MINOR} +1")
    set (libunfo_VERSION_PATCH 0)
    set (libunfo_RELEASE 1)
elseif (BUMP STREQUAL "3")
    MATH( EXPR libunfo_VERSION_MAJOR "${libunfo_VERSION_MAJOR} +1")
    set (libunfo_VERSION_MINOR 0)
    set (libunfo_VERSION_PATCH 0)
    set (libunfo_RELEASE 1)
endif()

configure_file(version.cmake.in
               version.cmake)
