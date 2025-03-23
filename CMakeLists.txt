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

if (MSVC)
    target_compile_options(Ormcy PRIVATE /W4 /Zl)
else()
    target_compile_options(Ormcy PRIVATE -Wall -Wextra -pedantic)
endif()