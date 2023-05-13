# Creates athenapp library

set(namel athenapp)
string(TOUPPER ${namel} nameu)

# source files are defined in Makefile.in
file(GLOB src_files
    src/*.cpp
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
    src/hydro/rsolvers/${RSOLVER_DIR}${RSOLVER_FILE}
    src/inputs/*.cpp
    src/mesh/*.cpp
    src/multigrid/*.cpp
    src/orbital_advection/*.cpp
    src/outputs/*.cpp
    src/pgen/default_pgen.cpp
    src/pgen/${PROBLEM_FILE}
    src/reconstruct/*.cpp
    src/scalars/*.cpp
    src/task_list/*.cpp
    src/utils/*.cpp
    ${MPIFFT_FILE}
  )

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

string(TOLOWER ${CMAKE_BUILD_TYPE} buildl)
string(TOUPPER ${CMAKE_BUILD_TYPE} buildu)

add_library(${namel}_${buildl} 
    OBJECT 
    ${src_files}
    )

set_target_properties(${namel}_${buildl}
    PROPERTIES
    COMPILE_FLAGS ${CMAKE_CXX_FLAGS_${buildu}}
    )

target_include_directories(${namel}_${buildl}
    SYSTEM PRIVATE
    ${MPI_CXX_INCLUDE_PATH}
    )

target_link_libraries(${namel}_${buildl}
    ${MPI_CXX_LIBRARIES}
    )

set(${nameu}_LIBRARY_${buildu} ${namel}_${buildl}
    CACHE STRING
    "{namel} library ${buildu}")
mark_as_advanced(${nameu}_LIBRARY_${buildu})

set(ATHENAPP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src
  CACHE PATH 
  "${namel} include directory")
mark_as_advanced(ATHENAPP_INCLUDE_DIR)
