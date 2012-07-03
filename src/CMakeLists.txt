cmake_minimum_required (VERSION 2.8)

# This project name is cyclopts.
project (CYCLOPTS)

# Direct any out-of-source builds to this directory
SET( CYCLOPTS_SRC_DIR ${CMAKE_SOURCE_DIR} )

# set module path
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)

# This makes all the libraries build as SHARED
SET(BUILD_SHARED_LIBS true)

# Setup build locations.
if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CYCLOPTS_BINARY_DIR}/bin)
endif()
if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CYCLOPTS_BINARY_DIR}/lib)
endif()
if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CYCLOPTS_BINARY_DIR}/lib)
endif()

SET(CYCLOPTS_EXECUTABLE_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Includes the directories in which there are source files. 
SET(CYCLOPTS_INCLUDE_DIR
  ${CYCLOPTS_SRC_DIR}
  ${CYCLOPTS_SRC_DIR}/Interface
  ${CYCLOPTS_SRC_DIR}/Solver
  ${CYCLOPTS_SRC_DIR}/Utility
  )

# Add any new core source files to this list.
SET( CYCLOPTS_SRC )

# Add any new core source files to this list.
SET( CYCLOPTS_INCL )

# add subdirectories
ADD_SUBDIRECTORY(Interface)
ADD_SUBDIRECTORY(Solver)
ADD_SUBDIRECTORY(Utility)

# find blas and link to it
FIND_PACKAGE( BLAS REQUIRED )
set(LIBS ${LIBS} ${BLAS_LIBRARIES})
MESSAGE("\tFound BLAS Libraries: ${BLAS_LIBRARIES}")

# find lapack and link to it
FIND_PACKAGE( LAPACK REQUIRED )
set(LIBS ${LIBS} ${LAPACK_LIBRARIES})
MESSAGE("\tFound LAPACK Libraries: ${LAPACK_LIBRARIES}")

# find coin and link to it
FIND_PACKAGE( COIN REQUIRED )
SET(CYCLOPTS_INCLUDE_DIR ${CYCLOPTS_INCLUDE_DIR} ${COIN_INCLUDE_DIRS})
set(LIBS ${LIBS} ${COIN_LIBRARIES})

# Include the boost header files and the program_options library
set(Boost_USE_STATIC_LIBS       OFF)
set(Boost_USE_STATIC_RUNTIME    OFF)
FIND_PACKAGE( Boost COMPONENTS program_options filesystem system REQUIRED)
SET(CYCLOPTS_INCLUDE_DIR ${CYCLOPTS_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})
set(LIBS ${LIBS} ${Boost_PROGRAM_OPTIONS_LIBRARY})
set(LIBS ${LIBS} ${Boost_SYSTEM_LIBRARY})
set(LIBS ${LIBS} ${Boost_FILESYSTEM_LIBRARY})
 
# include all the directories we just found
INCLUDE_DIRECTORIES( ${CYCLOPTS_INCLUDE_DIR} )

# Build the cyclopts library from the CYCLOPTS_SRC source files
ADD_LIBRARY( cyclopts ${CYCLOPTS_SRC} )
TARGET_LINK_LIBRARIES( cyclopts dl ${LIBS} )

#install the files
install(TARGETS cyclopts DESTINATION lib)
install(FILES ${CYCLOPTS_INCL} DESTINATION include)

# uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/Config/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)