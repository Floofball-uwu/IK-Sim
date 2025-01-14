#File modified
cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC
		"src/CCD.h"
		"src/FABRIK.h"
		"src/IKSolver.h"
		"src/Skeleton.h"
		"src/Skeleton.cpp"
		"src/Vector2.h"
		"src/Vector2.cpp"
)

add_library(ik-algorithms STATIC ${SRC})
target_include_directories(ik-algorithms PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Optional Example Project
option(BUILD_EXAMPLE "Build the example project" OFF)

if(BUILD_EXAMPLE)
	message(STATUS "Building example project")
	add_subdirectory(example)
endif()
