# Creates athenapp library

include_directories(
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/..
  ${CMAKE_BINARY_DIR}
  ${EIGEN3_INCLUDE_DIR}
  )

set(namel athenapp)
string(TOUPPER ${namel} nameu)

# set GENERAL_EOS_FILE, EOS_FILE, RSOLVER_DIR, RSOLVER_FILE, PROBLEM_FILE
set(GENERAL_EOS_FILE noop.cpp)
set(EOS_FILE ${EQUATION_OF_STATE})
set(RSOLVER_FILE ${RSOLVER})
set(PROBLEM_FILE ${PROBLEM})

if (MAGNETIC_FILEDS_ENABLED EQUAL 1)
    set(EOS_FILE ${EOS_FILE}_mhd)
    set(RSOLVER_DIR mhd/)
    set(RSOLVER_FILE ${RSOLVER_FILE}_mhd)
else()
    set(EOS_FILE ${EOS_FILE}_hydro)
    set(RSOLVER_DIR hydro/)
endif()

set(EOS_FILE ${EOS_FILE}.cpp)
set(RSOLVER_FILE ${RSOLVER_FILE}.cpp)
set(PROBLEM_FILE ${PROBLEM_FILE}.cpp)

# source files are defined in Makefile.in
file(GLOB src_files
    *.cpp
    bvals/*.cpp
    bvals/cc/*.cpp
    bvals/cc/fft_grav/*.cpp
    bvals/cc/hydro/*.cpp
    bvals/cc/mg/*.cpp
    bvals/cc/nr_radiation/*.cpp
    bvals/fc/*.cpp
    bvals/orbital/*.cpp
    bvals/utils/*.cpp
    coordinates/*.cpp
    eos/general/${GENERAL_EOS_FILE}
    eos/${EOS_FILE}
    eos/eos_high_order.cpp
    eos/eos_scalars.cpp
    fft/*.cpp
    field/*.cpp
    field/field_diffusion/*.cpp
    gravity/*.cpp
    hydro/*.cpp
    hydro/srcterms/*.cpp
    hydro/hydro_diffusion/*.cpp
    nr_radiation/*.cpp
    nr_radiation/integrators/*.cpp
    nr_radiation/integrators/srcterms/*.cpp
    nr_radiation/implicit/*.cpp
    cr/*.cpp
    cr/integrators/*.cpp
    hydro/rsolvers/${RSOLVER_DIR}${RSOLVER_FILE}
    inputs/*.cpp
    mesh/*.cpp
    multigrid/*.cpp
    orbital_advection/*.cpp
    outputs/*.cpp
    pgen/default_pgen.cpp
    pgen/${PROBLEM_FILE}
    reconstruct/*.cpp
    scalars/*.cpp
    task_list/*.cpp
    utils/*.cpp
    ${MPIFFT_FILE}
  )

# remove main file
list(FILTER src_files EXCLUDE REGEX ".*/src/main\\.cpp$")

string(TOLOWER ${CMAKE_BUILD_TYPE} buildl)
string(TOUPPER ${CMAKE_BUILD_TYPE} buildu)

add_library(${namel}_${buildl} 
    STATIC
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
    "{namel} library ${buildu}"
    )
mark_as_advanced(${nameu}_LIBRARY_${buildu})
