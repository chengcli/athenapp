# Creates the following benchmark tests
# shock_tube.cpp

string(TOLOWER ${CMAKE_BUILD_TYPE} buildl)
string(TOUPPER ${CMAKE_BUILD_TYPE} buildu)

# compile shock_tube.cpp
add_executable(shock_tube.${buildl} main.cpp shock_tube.cpp dummy.cpp)

set_target_properties(shock_tube.${buildl}
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
	COMPILE_FLAGS ${CMAKE_CXX_FLAGS_${buildu}}
	)

target_link_libraries(shock_tube.${buildl}
    ${ATHENAPP_LIBRARY_${buildu}}
	)

target_include_directories(shock_tube.${buildl}
	PRIVATE
    ${ATHENAPP_INCLUDE_DIR}
	)

# copy input files to build directory
file(GLOB infiles athinput.*)
foreach(infile ${infiles})
	get_filename_component(name ${infile} NAME)
	configure_file(${infile}
		${CMAKE_BINARY_DIR}/bin/${name} COPYONLY
		)
endforeach()
