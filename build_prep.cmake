include(chcommits.cmake)

MACRO(LIST_CONTAINS var value)
    SET(${var} FALSE)
    FOREACH (value2 ${ARGN})
        IF (${value} STREQUAL ${value2})
            SET(${var} TRUE)
        ENDIF (${value} STREQUAL ${value2})
    ENDFOREACH (value2 ${ARGN})
ENDMACRO(LIST_CONTAINS)

MACRO(FORMAT_LOG_ENTRY formated entry)
    string(REPLACE "\n" ";" entry_list ${entry})
    set(FMT_FINAL "")
    foreach(line ${entry_list})
        string(REGEX MATCH "^[ \n\t]+$" matched ${line})
        if (NOT ${line} STREQUAL "\n")
            string(REGEX REPLACE "^([^-])(.+)" "- \\1\\2" fmt_line ${line})
            set(FMT_FINAL "${FMT_FINAL}${fmt_line}\n")
        else()
        endif(NOT ${line} STREQUAL "\n")
    endforeach(line ${entry_list})
    set(formated ${FMT_FINAL})
ENDMACRO(FORMAT_LOG_ENTRY)

MACRO(MAKE_TAG_LOGENTRY tag_log_entry tag last_tag)
    exec_program("git" ARGS log ${tag} -n 1 --format="format:%ci%n"
                       OUTPUT_VARIABLE date)
    exec_program("date" ARGS -d"${date}" "\"+%a %b %d %Y\""
                        OUTPUT_VARIABLE DATE)
    exec_program("git" ARGS log ${tag} -n 1 --date=short
                            --format="format: %cn <%ce>%n"
                       OUTPUT_VARIABLE AUTHOR)
    exec_program("git" ARGS log ${tag} -n 1 --date=short
                            --format="format:%B%n"
                       OUTPUT_VARIABLE LOG)
    FORMAT_LOG_ENTRY(FMT_FINAL ${LOG})

    string(REPLACE "\n" "" mtl_tag_stripped ${tag})
    string(REPLACE "\n" "" mtl_lasttag_stripped ${last_tag})
    execute_process(COMMAND "git" describe --tags --exact-match ${mtl_tag_stripped}
                        OUTPUT_VARIABLE describe_out ERROR_VARIABLE describe_err)

    if (NOT ${describe_err} STREQUAL "")
        unset(describe_out)
        execute_process(COMMAND "git" describe --tags --exact-match ${mtl_lasttag_stripped}
                            OUTPUT_VARIABLE describe_out)
        execute_process(COMMAND "git" rev-parse --short ${mtl_tag_stripped}
                            OUTPUT_VARIABLE suffix)
        set(describe_out "${describe_out}.git${suffix}")
    endif(NOT ${describe_err} STREQUAL "")
    string(REPLACE "\n" "" TAG ${describe_out})

    string(REGEX REPLACE "^[la-z]+(-)?" "" mtl_tag_fmt ${TAG})
    string(REPLACE "\n" "" mtl_tag_out ${tag_out})

    set(tag_log_entry "* ${DATE} ${AUTHOR} ${mtl_tag_fmt}\n${FMT_FINAL}")
ENDMACRO(MAKE_TAG_LOGENTRY)

MACRO(MAKE_LOGENTRY log_entry commit)
    exec_program("git" ARGS log ${commit} -n 1 --date=short
                            --format="format:%B%n"
                        OUTPUT_VARIABLE LOG)
    FORMAT_LOG_ENTRY(FMT_FINAL ${LOG})
    set(log_entry "${FMT_FINAL}")
ENDMACRO(MAKE_LOGENTRY)

include (${CMAKE_SOURCE_DIR}/version.cmake)

set(CHANGELOG "")

execute_process(COMMAND "git" rev-parse --tags
                    OUTPUT_VARIABLE tags)
string(REGEX REPLACE "\n$" "" tags ${tags})
string(REPLACE "\n" ";" tags ${tags})

execute_process(COMMAND "git" "rev-parse" "--verify" "${TOP_COMMIT}^{commit}"
                    OUTPUT_VARIABLE top_commit)
string(REPLACE "\n" "" top_commit ${top_commit})

LIST_CONTAINS(contains ${top_commit} ${tags})
if (NOT contains)
    set(tags "${tags};${top_commit}")
    set(SOURCE_URL_PATH "archive/%{commit}/libunfo-%{commit}.tar.gz")
    set(archive_name "libunfo-${top_commit}.tar.gz")
else (NOT contains)
    execute_process(COMMAND "git" describe --tags --exact-match ${top_commit}
                        OUTPUT_VARIABLE describe_out ERROR_VARIABLE describe_err)
    string(REPLACE "\n" "" top_tag ${describe_out})
    set(SOURCE_URL_PATH "${top_tag}.tar.gz")
    set(archive_name "${top_tag}.tar.gz")
endif(NOT contains)

list(GET tags 0 last)
string(REPLACE "\n" "" last_tag ${last})

foreach(tag ${tags})
    string(REPLACE "\n" "" tag_out ${tag})
    execute_process(COMMAND "git" rev-parse --verify "${tag_out}^{commit}"
                        OUTPUT_VARIABLE tag_commit)
    string(REPLACE "\n" "" tag_commit ${tag_commit})

    MAKE_TAG_LOGENTRY(tag_log_entry ${tag_commit} ${last_tag})
    execute_process(COMMAND "git" "rev-list" "--all" ${tag_commit}
                        OUTPUT_VARIABLE commits)

    string(REGEX REPLACE "\n$" "" commits ${commits})
    string(REPLACE "\n" ";" commits ${commits})
    list(FIND commits ${tag_commit} index)
    list(LENGTH commits commits_len)

    math(EXPR clen "${commits_len}-1")

    foreach(i RANGE ${index} ${clen})
        list(GET commits ${i} commit)
        LIST_CONTAINS(contains1 ${commit} ${tags})
        LIST_CONTAINS(contains2 ${commit} ${changelog_commits})

        #message("index:${i}")
        #message("commit:${commit}")
        #message("tag:${tag_out}")
        #message("contains1:${contains1}")
        #message("contains2:${contains2}")
        if (contains1 AND NOT ${commit} STREQUAL ${tag_out})
            break()
        endif(contains1 AND NOT ${commit} STREQUAL ${tag_out})
        if (contains2)
            MAKE_LOGENTRY(log_entry ${commit})
            set(tag_log_entry ${tag_log_entry}${log_entry})
        endif(contains2)
    endforeach(i RANGE ${index} ${commits_len})

    set(CHANGELOG "${tag_log_entry}\n${CHANGELOG}")
    set(last_tag ${tag_out})
endforeach(tag ${tags})

IF (CMAKE_SIZEOF_VOID_P MATCHES "8")
    SET (LIB_SUFFIX "64")
ENDIF (CMAKE_SIZEOF_VOID_P MATCHES "8")


set(VERSION ${libunfo_VERSION_MAJOR}.${libunfo_VERSION_MINOR}.${libunfo_VERSION_PATCH})

exec_program("git" ARGS rev-parse --short HEAD OUTPUT_VARIABLE GITREV)
exec_program("git" ARGS rev-parse HEAD OUTPUT_VARIABLE GITREVLONG)

set(GITARG archive ${GITREV} "--format=tar.gz" "--prefix=libunfo-${GITREVLONG}/")
set(GITCMD "git")
execute_process(COMMAND ${GITCMD} ${GITARG} OUTPUT_FILE ${archive_name})

configure_file(libunfo.spec.in libunfo.spec)
configure_file(libunfo.pc.in libunfo.pc @ONLY)

