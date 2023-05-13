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
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/setup_parameter.cmake)

# remove main file
if (EXISTS "${CMAKE_SOURCE_DIR}/src/main.cpp")
  message(STATUS "Found main.cpp in ${CMAKE_SOURCE_DIR}/src/main.cpp")
  list(FILTER _src_files EXCLUDE REGEX ".*/src/main\\.cpp$")
endif()

# calcualte_fluxes delegates to user
if (EXISTS "${CMAKE_SOURCE_DIR}/src/hydro/calculate_fluxes.cpp")
    message(STATUS "Found calculate_fluxes.cpp in ${CMAKE_SOURCE_DIR}/src/hydro/calculate_fluxes.cpp")
    list(FILTER _src_files EXCLUDE REGEX ".*/src/hydro/calculate_fluxes\\.cpp$")
endif()

# new_blockdt delegates to user
if (EXISTS "${CMAKE_SOURCE_DIR}/src/hydro/new_blockdt.cpp")
    message(STATUS "Found new_blockdt.cpp in ${CMAKE_SOURCE_DIR}/src/hydro/new_blockdt.cpp")
    list(FILTER _src_files EXCLUDE REGEX ".*/src/hydro/new_blockdt\\.cpp$")
endif()

# outputs delegates to user
if (EXISTS "${CMAKE_SOURCE_DIR}/outputs/outputs.cpp")
    message(STATUS "Found outputs.cpp in ${CMAKE_SOURCE_DIR}/outputs/outputs.cpp")
    list(FILTER _src_files EXCLUDE REGEX ".*/src/outputs/outputs\\.cpp$")
endif()

## 3. set up project system libraries ##
if (${MPI_OPTION} STREQUAL "MPI_PARALLEL")
    find_package(MPI REQUIRED)
endif()

## 4. set up project configure file and library ##
message(STATUS "4. Set up project libraries")
configure_file(src/defs.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/src/defs.hpp @ONLY)
add_subdirectory(src)

#include_directories(
#  ${CMAKE_CURRENT_BINARY_DIR}
#  )
