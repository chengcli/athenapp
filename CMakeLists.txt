# Installs athenapp library
#
#   library: libathenapp_debug.a
#   library: libathenapp_release.a
#
# Define the following variables
#
#   ATHENAPP_INCLUDE_DIR
#   ATHENAPP_LIBRARY_DEBUG
#   ATHENAPP_LIBRARY_RELEASE
#
# Normal usage would be
#
#   include_directories( ${ATHENAPP_INCLUDE_DIR})
#   target_link_libraries( ${ATHENAPP_LIBRARY_DEBUG})
#
cmake_minimum_required(VERSION 3.10)

project(
  ATHENAPP
  LANGUAGES CXX
  )
set(CMAKE_CXX_STANDARD 14)
message(STATUS "")
message(STATUS "== Setting up athenapp library ==")

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
  message(STATUS "Default Build Type = Release")
  message(STATUS "")
else()
  message(STATUS "Build Type = ${CMAKE_BUILD_TYPE}")
  message(STATUS "")
endif()

## 1. set up compiler flags ##
message(STATUS "1. Set up project compiler flags ...")
message(STATUS "Include ${CMAKE_SOURCE_DIR}/cmake/setup_compiler_flags.cmake")
include(${CMAKE_SOURCE_DIR}/cmake/setup_compiler_flags.cmake)

## 2. set up project specific configuration ##
message(STATUS "2. Set up project specific configuration ...")
message(STATUS "Include ${CMAKE_CURRENT_SOURCE_DIR}/cmake/setup_parameters.cmake")
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/setup_parameters.cmake)

## 3. set up project system libraries ##
message(STATUS "3. Set up project system libraries ...")
if (${MPI_OPTION} STREQUAL "MPI_PARALLEL")
    find_package(MPI REQUIRED)
endif()

## 4. set up project configure file and library ##
message(STATUS "4. Set up project libraries ...")
message(STATUS "Find project definitions in src/defs.hpp")
configure_file(src/defs.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/src/defs.hpp @ONLY)
add_subdirectory(src)

## 5. set up project benchmark tests ##
message(STATUS "5. Set up benchmark tests ...")
add_subdirectory(bench)

#include_directories(
#  ${CMAKE_CURRENT_BINARY_DIR}
#  )
