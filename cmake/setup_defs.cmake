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

set(EOS_FILE ${EquationOfState}.cpp)

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

if (DEFINED MPIOption)
  set(MPI_OPTION ${MPIOption})
else()
  set(MPI_OPTION NOT_MPI_PARALLEL)
endif()

if (DEFINED CubedSphereOption)
  set(CUBED_SPHERE_OPTION ${CubedSphereOption})
else()
  set(CUBED_SPHERE_OPTION NOT_CUBED_SPHERE)
endif()

set(OPENMP_OPTION NOT_OPENMP_PARALLEL)

set(HDF5_OPTION NO_NDF5OUTPUT_PARALLEL)

set(DEBUG_OPTION NOT_DEBUG)

#set(EXCEPTION_HANDLING_OPTION DISABLE_EXCEPTIONS)
set(EXCEPTION_HANDLING_OPTION ENABLE_EXCEPTIONS)

if (${NumVapors})
  math(EXPR NHYDRO_VARIABLES "5 + ${NumVapors}")
  set(NVAPOR_VARIABLES ${NumVapors})
else()
  set(NHYDRO_VARIABLES 5)
  set(NVAPOR_VARIABLES 0)
endif()

set(NFIELD_VARIABLES 0)

set(NWAVE_VALUE ${NHYDRO_VARIABLES})

if (${NumScalars})
  set(NUMBER_PASSIVE_SCALARS ${NumScalars})
else()
  set(NUMBER_PASSIVE_SCALARS 0)
endif()

set(NUMBER_GHOST_CELLS ${GhostZoneSize})
