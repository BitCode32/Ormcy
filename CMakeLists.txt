cmake_minimum_required(VERSION 3.10)
project(Ormcy C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(LIB_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Lib/Headers")

if(WIN32)
    set (HALLOCY_LIB_PATH "${CMAKE_SOURCE_DIR}/Lib/Windows/Hallocy.lib")
elseif(UNIX)
    set (HALLOCY_LIB_PATH "${CMAKE_SOURCE_DIR}/Lib/Linux/libHallocy.a")
endif()

include_directories(${PROJECT_SOURCE_DIR}/Include)
include_directories(${LIB_INCLUDE_DIR})
file(GLOB_RECURSE SRC_FILES "${PROJECT_SOURCE_DIR}/Src/*.c")

add_library(Ormcy STATIC ${SRC_FILES})
add_executable(OrmcyApp ${PROJECT_SOURCE_DIR}/Src/Main.c)

target_link_libraries(Ormcy PRIVATE ${HALLOCY_LIB_PATH})
target_link_libraries(OrmcyApp Ormcy)

if (ORMCY_POSTGRESQL)
    if (WIN32)
    find_path(LIBPQ_INCLUDE_DIR libpq-fe.h
        PATHS "C:/Program Files/PostgreSQL" "C:/PostgreSQL"
        PATH_SUFFIXES "17/include" "include"
        NO_DEFAULT_PATH
    )

    find_library(LIBPQ_LIBRARY NAMES libpq
        PATHS "C:/Program Files/PostgreSQL" "C:/PostgreSQL"
        PATH_SUFFIXES "17/lib" "lib"
        NO_DEFAULT_PATH
    )
    elseif(UNIX)
        find_path(LIBPQ_INCLUDE_DIR postgresql/libpq-fe.h PATHS "/usr/include" "/usr/local/include")
        find_library(LIBPQ_LIBRARY NAMES pq PATHS "/usr/lib" "/usr/local/lib")
    endif()

    if (NOT LIBPQ_INCLUDE_DIR OR NOT LIBPQ_LIBRARY)
        message(FATAL_ERROR "PostgreSQL libpq not found! Install libpq-dev on Linux or specify path manually on Windows.")
    endif()

    target_link_libraries(Ormcy PRIVATE ${HALLOCY_LIB_PATH} ${LIBPQ_LIBRARY})
    target_include_directories(Ormcy PRIVATE ${LIBPQ_INCLUDE_DIR})
    target_link_libraries(OrmcyApp Ormcy ${LIBPQ_LIBRARY})
    target_include_directories(OrmcyApp PRIVATE ${LIBPQ_INCLUDE_DIR})

    add_compile_definitions(ORMCY_POSTGRESQL)
endif()

if (MSVC)
    target_compile_options(Ormcy PRIVATE /W4 /Zl)
else()
    target_compile_options(Ormcy PRIVATE -Wall -Wextra -pedantic)
endif()