# Leng cmake build script.
cmake_minimum_required(VERSION 2.8)
project(AGPU)

# Check the build type
if (CMAKE_BUILD_TYPE STREQUAL "")
	# CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
	# differentiation between debug and release builds.
	set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Output paths.
set(CMAKE_DEBUG_POSTFIX "_d")
 
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/dist")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/;${CMAKE_MODULE_PATH}")

# Turn warnings
if ("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
	# using Visual Studio C++
	set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
	set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c11")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
endif()

# Find OpenGL
find_package(OpenGL)

# Add some include directories
include_directories(. include)

# Set output dir.
set(EXECUTABLE_OUTPUT_PATH "${AGPU_BINARY_DIR}/dist")
set(LIBRARY_OUTPUT_PATH "${AGPU_BINARY_DIR}/dist")

# Try to use pkg-config.
find_package(PkgConfig)
if(PKG_CONFIG_FOUND)

    # Find SDL2
    pkg_check_modules(SDL2 REQUIRED sdl2)
    include_directories(${SDL2_INCLUDE_DIRS})

    # Find unittest++
    pkg_check_modules(UNITTESTMM unittest++)
    if(UNITTESTMM_FOUND)
        include_directories(${UNITTESTMM_INCLUDE_DIRS})
    endif()

else()
    # For VisualStudio in Window
    find_path(SDL2_INCLUDE_DIR
      NAMES SDL.h
    )

    find_path(SDL2_LIBRARY_PATH
      NAMES SDL2.lib SDL2.a
    )

    find_library(SDL2_LIBRARY NAMES SDL2 PATHS ${SDL2_LIBRARY_PATH})
	find_library(SDL2_MAIN_LIBRARY NAMES SDL2main PATHS ${SDL2_LIBRARY_PATH})

endif()

# Samples libraries
set(AGPU_MAIN_LIB AgpuOpenGL)
set(AGPU_SAMPLES_LIBS ${AGPU_SAMPLES_LIBS} ${SDL2_LIBRARIES} ${AGPU_MAIN_LIB})

# Build the implementations
add_subdirectory(implementations)

add_subdirectory(samples)

# Build the tests.
if(UNITTESTMM_FOUND)
    add_subdirectory(tests)
endif()