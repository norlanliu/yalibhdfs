cmake_minimum_required (VERSION 2.8)

project (yalibhdfs CXX)

set(CXX_FLAGS
 -g
 -Wall
 -Wextra
 -std=c++11
 -Wconversion
 -Wunused-parameter
 -Wold-style-cast
 -MMD
 -Wpointer-arith
 -Wshadow
 -Wwrite-strings
 -rdynamic
 -levent_core
 -lxml2
 -levent_extra
 -levent_pthreads
 -lglog
 -lprotobuf
 -lpthread
 )
FIND_PACKAGE(LibXml2 REQUIRED)

string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

include(Functions)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src/utility)
include_directories(${PROJECT_BINARY_DIR})
add_subdirectory(src)
add_subdirectory(test)

