#!/bin/cmake -P

include(version.cmake)
execute_process(COMMAND "git" tag 
                "libunfo-${libunfo_VERSION_MAJOR}.${libunfo_VERSION_MINOR}.${libunfo_VERSION_PATCH}"
                    OUTPUT_VARIABLE describe_out ERROR_VARIABLE describe_err)
