################################
## set up model configuration ##
################################

# general configuration

set(PROBLEM "default")

set(COORDINATE_SYSTEM "${CoordinateSystem}")

set(RSOLVER "${RiemannSolver}")

set(EQUATION_OF_STATE "adiabatic")

# specific compile files

set(GENERAL_EOS_FILE noop.cpp)

#if (${EquationOfState} STREQUAL "adiabatic_hydro")
#  set(EOS_FILE ${CMAKE_CURRENT_SOURCE_DIR}/src/eos/${EquationOfState}.cpp)
#else()
#  set(EOS_FILE ${CMAKE_SOURCE_DIR}/src/eos/${EquationOfState}.cpp)
#endif()

set(RSOLVER_FILE ${RiemannSolver}.cpp)

# parameters

set(GENERAL_EOS 0)

set(EOS_TABLE_ENABLED 0)

set(NON_BAROTROPIC_EOS 1)

set(MAGNETIC_FIELDS_ENABLED 0)

set(STS_ENABLED 0)

set(SELF_GRAVITY_ENABLED 0)

set(RELATIVISTIC_DYNAMICS 0)

set(GENERAL_RELATIVITY 0)

set(FRAME_TRANSFORMATIONS 0)

if (${SinglePrecision})
  set(SINGLE_PRECISION_ENABLED 1)
else()
  set(SINGLE_PRECISION_ENABLED 0)
endif()

set(H5_DOUBLE_PRECISION_ENABLED 0)

set(FFT_OPTION NO_FFT)

set(MPI_OPTION ${EnableMPI})

set(OPENMP_OPTION NOT_OPENMP_PARALLEL)

set(HDF5_OPTION NO_NDF5OUTPUT_PARALLEL)

set(DEBUG_OPTION NOT_DEBUG)

#set(EXCEPTION_HANDLING_OPTION DISABLE_EXCEPTIONS)
set(EXCEPTION_HANDLING_OPTION ENABLE_EXCEPTIONS)

math(EXPR NHYDRO_VARIABLES "5 + ${NumVapors}")
set(NVAPOR_VARIABLES ${NumVapors})

set(NFIELD_VARIABLES 0)

set(NWAVE_VALUE ${NHYDRO_VARIABLES})

set(NUMBER_PASSIVE_SCALARS ${NumTracers})

set(NUMBER_GHOST_CELLS ${GhostZoneSize})
