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
message(STATUS "== Setting up athenapp library ==")

# set up model parameters
message(STATUS "Include ${CMAKE_SOURCE_DIR}/cmake/setup_configure.cmake")
include(${CMAKE_SOURCE_DIR}/cmake/setup_configure.cmake)

message(STATUS "Include ${CMAKE_CURRENT_SOURCE_DIR}/cmake/setup_defs.cmake")
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/setup_defs.cmake)
configure_file(src/defs.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/src/defs.hpp @ONLY)

file(GLOB _src_files
  src/parameter_input.cpp
  src/globals.cpp
  src/bvals/*.cpp
  src/bvals/cc/*.cpp
  src/bvals/cc/fft_grav/*.cpp
  src/bvals/cc/hydro/*.cpp
  src/bvals/cc/mg/*.cpp
  src/bvals/fc/*.cpp
  src/bvals/orbital/*.cpp
  src/bvals/utils/*.cpp
  src/coordinates/*.cpp
  src/eos/general/${GENERAL_EOS_FILE}
  src/eos/${EOS_FILE}
  src/eos/eos_high_order.cpp
  src/eos/eos_scalars.cpp
  src/fft/*.cpp
  src/field/*.cpp
  src/field/field_diffusion/*.cpp
  src/gravity/*.cpp
  src/hydro/*.cpp
  src/hydro/srcterms/*.cpp
  src/hydro/hydro_diffusion/*.cpp
  src/hydro/rsolvers/hydro/${RSOLVER_FILE}
  src/inputs/*.cpp
  src/mesh/*.cpp
  src/multigrid/*.cpp
  src/orbital_advection/*.cpp
  src/outputs/*.cpp
  src/pgen/default_pgen.cpp
  src/reconstruct/*.cpp
  src/scalars/*.cpp
  src/task_list/*.cpp
  src/utils/*.cpp
  )

# EOS_FILE delegates to user
#list(APPEND _src_files ${EOS_FILE})

# calcualte_fluxes delegates to user
list(FILTER _src_files EXCLUDE REGEX ".*/src/hydro/calculate_fluxes\\.cpp$")

# new_blockdt delegates to user
list(FILTER _src_files EXCLUDE REGEX ".*/src/hydro/new_blockdt\\.cpp$")

# outputs delegates to user
list(FILTER _src_files EXCLUDE REGEX ".*/src/outputs/outputs\\.cpp$")

#include_directories(
#  ${CMAKE_CURRENT_BINARY_DIR}
#  )

foreach(build ${BUILD_TYPES})
  string(TOLOWER ${build} buildl)
  add_library(athenapp_${buildl} OBJECT ${_src_files})

  set_target_properties(athenapp_${buildl}
    PROPERTIES
    COMPILE_FLAGS ${CMAKE_CXX_FLAGS_${build}}
    )

  target_include_directories(athenapp_${buildl}
    SYSTEM PRIVATE
    ${MPI_CXX_INCLUDE_PATH}
    )

  target_link_libraries(athenapp_${buildl}
    ${MPI_CXX_LIBRARIES}
    )

  set(ATHENAPP_LIBRARY_${build} athenapp_${buildl}
    CACHE STRING
    "athenapp library ${build}")
  mark_as_advanced(ATHENAPP_LIBRARY_${build})
endforeach()

set(ATHENAPP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src
  CACHE PATH 
  "athenapp include directory")
mark_as_advanced(ATHENAPP_INCLUDE_DIR)
