## defines default parameters

## define a macro to set a variable if it is empty
macro(SET_IF_EMPTY _variable)
    if("${${_variable}}" STREQUAL "")
        set(${_variable} ${ARGN})
    endiF()
endmacro()

## populate the default values

## configure.py dict(definitions) string values:
# problem generator
SET_IF_EMPTY(PROBLEM "default")

# coordinate system
SET_IF_EMPTY(COORDINATE_SYSTEM "cartesian")

# Riemann solver
SET_IF_EMPTY(RSOLVER "hllc")

# Equation of state
SET_IF_EMPTY(EQUATION_OF_STATE "adiabatic")

# ChemNetwork class header file included in species.hpp
SET_IF_EMPTY(CHEMNETWORK_HEADER "../chemistry/network/chem_network.hpp")

# ChemRadiation integrator method, used in constructing ChemRadiationIntegratorTaskList
SET_IF_EMPTY(CHEMRADIATION_INTEGRATOR "none")

## configure.py dict(definitions) Boolean values:
# use general EOS framework default=0 (false).
SET_IF_EMPTY(GENERAL_EOS 0)

# use EOS table default=0 (false).
SET_IF_EMPTY(EOS_TABLE_ENABLED 0)

# non-barotropic equation of state (i.e. P not simply a func of rho)? default=1 (true)
SET_IF_EMPTY(NON_BAROTROPIC_EOS 1)

# include magnetic fields? default=0 (false)
SET_IF_EMPTY(MAGNETIC_FIELDS_ENABLED 0)

# include super-time-stepping? default=0 (false)
SET_IF_EMPTY(STS_ENABLED 0)

# include self gravity? default=0 (false)
SET_IF_EMPTY(SELF_GRAVITY_ENABLED 0)

# include chemistry? default=0 (false)
SET_IF_EMPTY(CHEMISTRY_ENABLED 0)

# include radiative transfer in chemistry calculations? default=0 (false)
SET_IF_EMPTY(CHEMRADIATION_ENABLED 0)

# include nonrelativistic radiative transfer? default=0 (false)
SET_IF_EMPTY(NR_RADIATION_ENABLED 0)

# include radiative transfer evolved with implicit method? default=0 (false)
SET_IF_EMPTY(IM_RADIATION_ENABLED 0)

# include cosmic ray transport? default=0 (false)
SET_IF_EMPTY(CR_ENABLED 0)

# include cosmic ray diffusion? default=0 (false)
SET_IF_EMPTY(CRDIFFUSION_ENABLED 0)

# enable special or general relativity? default=0 (false)
SET_IF_EMPTY(RELATIVISTIC_DYNAMICS 0)

# enable general relativity? default=0 (false)
SET_IF_EMPTY(GENERAL_RELATIVITY 0)

# enable GR frame transformations? default=0 (false)
SET_IF_EMPTY(FRAME_TRANSFORMATIONS 0)

# use single precision floating-point values (binary32)? default=0 (false; use binary64)
SET_IF_EMPTY(SINGLE_PRECISION_ENABLED 0)

# use double precision for HDF5 output? default=0 (false; write out binary32)
SET_IF_EMPTY(H5_DOUBLE_PRECISION_ENABLED 0)

# compile with debug symbols and use optional sections of source code? default=0 (false)
SET_IF_EMPTY(DEBUG_OPTION 0)

## configure.py dict(definitions) Boolean string macros:
## (these options have the latter (false) option as defaults, unless noted otherwise)

# FFTW library (FFT or NO_FFT)
SET_IF_EMPTY(FFT_OPTION "NO_FFT")

# CVODE solver (CVODE or NO_CVODE)
SET_IF_EMPTY(CVODE_OPTION "NO_CVODE")

# MPI parallelization (MPI_PARALLEL or NOT_MPI_PARALLEL)
SET_IF_EMPTY(MPI_OPTION "NOT_MPI_PARALLEL")

IF(MPI_OPTION STREQUAL "MPI_PARALLEL")
  find_package(MPI COMPONENTS CXX REQUIRED)
endif()

# OpenMP parallelization (OPENMP_PARALLEL or NOT_OPENMP_PARALLEL)
SET_IF_EMPTY(OPENMP_OPTION "NOT_OPENMP_PARALLEL")

# HDF5 output (HDF5OUTPUT or NO_HDF5OUTPUT)
SET_IF_EMPTY(HDF5_OPTION "NO_HDF5OUTPUT")

# NetCDF output (NETCDFOUTPUT or NO_NETCDFOUTPUT)
SET_IF_EMPTY(NETCDF_OPTION "NO_NETCDFOUTPUT")

# PNetCDF output (PNETCDFOUTPUT or NO_PNETCDFOUTPUT)
SET_IF_EMPTY(PNETCDF_OPTION "NO_PNETCDFOUTPUT")

# FITS output (FITSOUTPUT or NO_FITSOUTPUT)
SET_IF_EMPTY(FITS_OPTION "NO_FITSOUTPUT")

# try/throw/catch C++ exception handling (ENABLE_EXCEPTIONS or DISABLE_EXCEPTIONS)
SET_IF_EMPTY(EXCEPTION_HANDLING_OPTION "ENABLE_EXCEPTIONS")

# hydrostatic option (HYDROSTATIC or NOT_HYDROSTATIC)
SET_IF_EMPTY(HYDROSTATIC_OPTION "NOT_HYDROSTATIC")

# compiler options
SET_IF_EMPTY(COMPILER_CHOICE ${CMAKE_CXX_COMPILER_ID})
SET_IF_EMPTY(COMPILER_COMMAND ${CMAKE_CXX_COMPILER})
string(TOUPPER ${CMAKE_BUILD_TYPE} BUILD_TYPE)
SET_IF_EMPTY(COMPILER_FLAGS ${CMAKE_CXX_FLAGS_${BUILD_TYPE}})

# macros associated with numerical algorithm (rarely modified)
SET_IF_EMPTY(NVAPOR 0)
SET_IF_EMPTY(NCLOUD 0)
SET_IF_EMPTY(NMASS 0)
SET_IF_EMPTY(NCHEM 0)

SET_IF_EMPTY(NFIELD_VARIABLES 0)
SET_IF_EMPTY(NUMBER_GHOST_CELLS 2)
SET_IF_EMPTY(NUMBER_CHEMICAL_SPECIES 0)

if(NON_BAROTROPIC_EOS EQUAL 1)
  math(EXPR NHYDRO_VARIABLES "5 + ${NVAPOR} + ${NCLOUD}")
else()
  math(EXPR NHYDRO_VARIABLES "4 + ${NVAPOR} + ${NCLOUD}")
endif()

if(MAGNETIC_FIELDS_ENABLED EQUAL 0)
  set(NWAVE_VALUE ${NHYDRO_VARIABLES})
else()
  math(EXPR NWAVE_VALUE "2 + ${NHYDRO_VARIABLES}")
endif()

if(NR_RADIATION_ENABLED EQUAL 0)
  SET_IF_EMPTY(NRAD_VARIABLES 0)
else()
  SET_IF_EMPTY(NRAD_VARIABLES 14)
endif()

if(IM_RADIATION_ENABLED EQUAL 0)
  SET_IF_EMPTY(NRAD_VARIABLES 0)
else()
  SET_IF_EMPTY(NRAD_VARIABLES 14)
endif()

if(CR_ENABLED EQUAL 0)
  SET_IF_EMPTY(NCR_VARIABLES 0)
else()
  SET_IF_EMPTY(NCR_VARIABLES 4)
endif()

SET_IF_EMPTY(NGRAV_VARIABLES 0)

SET_IF_EMPTY(NTURBULENCE 0)

math(EXPR NUMBER_PASSIVE_SCALARS "${NMASS} + ${NCHEM}")
