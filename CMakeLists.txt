
cmake_minimum_required(VERSION 2.6)
project(GLFWDemo C CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
add_definitions( -DSRC_DIR="${CMAKE_CURRENT_SOURCE_DIR}/src" )
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	add_definitions( -DUSE_APPLE )
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

# Had to install:
# libxrandr-dev
# libxinerama-dev
# libxcursor-dev
#

# GLFW
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw-3.1.2 )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw-3.1.2/include )

# Create the executable
set( SRCS
	${CMAKE_CURRENT_SOURCE_DIR}/src/BasicTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ShaderStuff.hpp
)
add_executable( BasicTest ${SRCS} )
target_link_libraries( BasicTest ${glfw_LIBRARIES} )

