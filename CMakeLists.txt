cmake_minimum_required(VERSION 3.10)
project(Piscine C)
set(CMAKE_C_STANDARD 99)


if (WIN32)
    find_path(MYSQL_INCLUDE_DIR
            NAMES "mysql.h"
            PATHS "include")

    find_library(MYSQL_LIBRARY
            NAMES "libmysql.dll"
            PATHS "lib")
else ()
    find_path(MYSQL_INCLUDE_DIR
            NAMES "mysql.h"
            PATHS "/usr/include/mysql"
            "/usr/local/include/mysql"
            "/usr/mysql/include/mysql")

    find_library(MYSQL_LIBRARY
            NAMES "mysqlclient" "mysqlclient_r"
            PATHS "/lib/mysql"
            "/lib64/mysql"
            "/usr/lib/mysql"
            "/usr/lib64/mysql"
            "/usr/local/lib/mysql"
            "/usr/local/lib64/mysql"
            "/usr/mysql/lib/mysql"
            "/usr/mysql/lib64/mysql")
endif ()


if (MYSQL_INCLUDE_DIR AND EXISTS "${MYSQL_INCLUDE_DIRS}/mysql_version.h")
    file(STRINGS "${MYSQL_INCLUDE_DIRS}/mysql_version.h"
            MYSQL_VERSION_H REGEX "^#define[ \t]+MYSQL_SERVER_VERSION[ \t]+\"[^\"]+\".*$")
    string(REGEX REPLACE
            "^.*MYSQL_SERVER_VERSION[ \t]+\"([^\"]+)\".*$" "\\1" MYSQL_VERSION_STRING
            "${MYSQL_VERSION_H}")
endif ()

# handle the QUIETLY and REQUIRED arguments and set MYSQL_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MYSQL DEFAULT_MSG
        REQUIRED_VARS MYSQL_LIBRARY MYSQL_INCLUDE_DIR
        VERSION_VAR MYSQL_VERSION_STRING)

set(MYSQL_INCLUDE_DIRS ${MYSQL_INCLUDE_DIR})
set(MYSQL_LIBRARIES ${MYSQL_LIBRARY})

mark_as_advanced(MYSQL_INCLUDE_DIR MYSQL_LIBRARY)

# Library database
add_library(
        DatabaseLibrary
        source/database.c
        source/database.h
        source/access/ingredient.c
        source/access/ingredient.h
        source/access/recipe.c
        source/access/recipe.h
        source/access/quantity.c
        source/access/quantity.h
        source/ihm.c
        source/ihm.h
)


# Main
add_executable(piscine_c source/main.c)
target_link_libraries(piscine_c ${MYSQL_LIBRARY} DatabaseLibrary)


# Tests
add_executable(tests_db_access tests/test_db_access.c)
target_link_libraries(tests_db_access ${MYSQL_LIBRARY} DatabaseLibrary)
