## set up configuration for athenapp ##

if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
  set(CMAKE_BUILD_TYPE "Debug")
endif()

# float point operation precision
option(SinglePrecision "Enable single precision" OFF)

# equation of state
set(EquationOfState adiabatic_hydro
  CACHE STRING "Choose the equation of state for primitive-conserved conversion")
set_property(CACHE EquationOfState
  PROPERTY STRINGS
  adiabatic_hydro
  ideal_moist_hydro
  )

# coordinate system
set(CoordinateSystem cartesian
  CACHE STRING "Choose the coordinate system of the problem")
set_property(CACHE CoordinateSystem
  PROPERTY STRINGS
  cartesian
  cylindrical
  spherical_polar
  minkowski
  sinusoidal
  tilted
  schwarzschild
  kerr-schild
  gr_user
  gnomonic_equiangle
  affine_coordinates
  )

# hydro flux solver
set(RiemannSolver hllc
  CACHE STRING "Choose the Riemann Solver")

# ghost zone size
set(GhostZoneSize 3
  CACHE STRING "Set ghose zone size")

# array size
set(NumVapors 0
  CACHE STRING "Set number of vapors in the equation of state")
set(NumScalars 0
  CACHE STRING "Set number of fluid tracers")

# MPI flag
#option(UseMPI "Enable MPI" OFF)
if (${UseMPI})
  find_package(MPI REQUIRED)
  set(MPIOption MPI_PARALLEL)
else()
  set(MPIOption NOT_MPI_PARALLEL)
endif()

# CubedSphere flag
if (${UseCubedSphere})
  set(CubedSphereOption CUBED_SPHERE)
  set(CoordinateSystem gnomonic_equiangle)
else()
  set(CubedSphereOption NOT_CUBED_SPHERE)
endif()

if (CMAKE_BUILD_TYPE MATCHES "Debug")
  if (NOT "DEBUG" IN_LIST BUILD_TYPES)
    list(APPEND BUILD_TYPES "DEBUG")
  endif()
endif()

if (CMAKE_BUILD_TYPE MATCHES "Release")
  if (NOT "RELEASE" IN_LIST BUILD_TYPES)
    list(APPEND BUILD_TYPES "RELEASE")
  endif()
endif()
