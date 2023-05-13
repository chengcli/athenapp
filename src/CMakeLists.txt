
# source files are defined in Makefile.in
file(GLOB _src_files
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
