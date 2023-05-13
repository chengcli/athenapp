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
SET_IF_EMPTY(PROBLEM "shock_tube")

# coordinate system
SET_IF_EMPTY(COORDINATE_SYSTEM "cartesian")

# Riemann solver
SET_IF_EMPTY(RSOLVER "hllc")

# Equation of state
SET_IF_EMPTY(EQUATION_OF_STATE "adiabatic")

## configure.py dict(definitions) Boolean values:
# use general EOS framework default=0 (false).
SET_IF_EMPTY(GENERAL_EOS 0)

# use EOS table default=0 (false).
SET_IF_EMPTY(EOS_TABLE_ENABLED 0)

# non-barotropic equation of state (i.e. P not simply a func of rho)? default=1 (true)
SET_IF_EMPTY(NON_BAROTROPIC_EOS 1)

# include magnetic fields? default=0 (false)
SET_IF_EMPTY(MAGNETIC_FIELDS_ENABLE 0)

# include super-time-stepping? default=0 (false)
SET_IF_EMPTY(STS_ENABLE 0)

# include self gravity? default=0 (false)
SET_IF_EMPTY(SELF_GRAVITY_ENABLE 0)

# include radiative transfer? default=0 (false)
SET_IF_EMPTY(RADIATION_ENABLE 0)

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

## configure.py dict(definitions) Boolean string macros:
## (these options have the latter (false) option as defaults, unless noted otherwise)
# make use of FFT? (FFT or NO_FFT)
SET_IF_EMPTY(FFT_OPTION "NO_FFT")

# MPI parallelization (MPI_PARALLEL or NOT_MPI_PARALLEL)
SET_IF_EMPTY(MPI_OPTION "NOT_MPI_PARALLEL")

# OpenMP parallelization (OPENMP_PARALLEL or NOT_OPENMP_PARALLEL)
SET_IF_EMPTY(OPENMP_OPTION "NOT_OPENMP_PARALLEL")

# HDF5 output (HDF5OUTPUT or NO_HDF5OUTPUT)
SET_IF_EMPTY(HDF5_OPTION "NO_HDF5OUTPUT")

# debug build macros (DEBUG or NOT_DEBUG)
SET_IF_EMPTY(DEBUG_OPTION "NOT_DEBUG")

# try/throw/catch C++ exception handling (ENABLE_EXCEPTIONS or DISABLE_EXCEPTIONS)
SET_IF_EMPTY(EXCEPTIONS_OPTION "ENABLE_EXCEPTIONS")

# compiler options
SET_IF_EMPTY(COMPILER_CHOICES ${CMAKE_CXX_COMPILER_ID})
SET_IF_EMPTY(COMPILER_COMMAND ${CMAKE_CXX_COMPILER_COMMAND})
string(TOUPPER ${CMAKE_BUILD_TYPE} BUILD_TYPE)
SET_IF_EMPTY(COMPILER_FLAGS ${CMAKE_CXX_FLAGS_${BUILD_TYPE}})

# macros associated with numerical algorithm (rarely modified)
SET_IF_EMPTY(NHYDRO_VARIABLES 5)
SET_IF_EMPTY(NFIELD_VARIABLES 0)
SET_IF_EMPTY(NWAVE 5)
SET_IF_EMPTY(NSCALARS 0)
SET_IF_EMPTY(NGHOST 2)
