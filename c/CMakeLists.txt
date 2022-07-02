cmake_minimum_required(VERSION 2.8)
set(CMAKE_VERBOSE_MAKEFILE ON)
set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )

project(c C)

set(CMAKE_C_FLAGS "-g")
#set(CMAKE_CXX_FLAGS "-g -pthread -std=c++0x -pipe -fPIC")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wunused-parameter -Woverloaded-virtual -Wpointer-arith -Wshadow -Wwrite-strings -Wcast-align")

message(STATUS ${CMAKE_BUILD_TYPE})
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")

set(ROOT_DIR ${CMAKE_SOURCE_DIR})
message(${ROOT_DIR})
include_directories(/usr/local/include ${ROOT_DIR})
include_directories(/usr/lib/include)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../output)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../output)

link_directories(/usr/local/lib)

if(APPLE)
  message(STATUS "os: APPLE")
  #set(COMMON_LIBS pthread)
elseif(UNIX)
  message(STATUS "os: UNIX")
  set(COMMON_LIBS pthread rt)
endif()

add_executable(testmemcpy app/testmemcpy/testmemcpy.c)
target_link_libraries(testmemcpy ${COMMON_LIBS})
