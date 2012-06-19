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

# add subdirectories
ADD_SUBDIRECTORY(Interface)
ADD_SUBDIRECTORY(Solver)
ADD_SUBDIRECTORY(Utility)

# find coin and link to it
FIND_PACKAGE( COIN REQUIRED )
SET(CYCLOPTS_INCLUDE_DIR ${CYCLOPTS_INCLUDE_DIR} ${COIN_INCLUDE_DIRS})
set(LIBS ${LIBS} ${COIN_LIBRARIES})

# include all the directories we just found
INCLUDE_DIRECTORIES( ${CYCLOPTS_INCLUDE_DIR} )

# Build the cyclopts executable from the CYCLOPTS_SRC source files
ADD_EXECUTABLE( cyclopts ${CYCLOPTS_SRC} )
TARGET_LINK_LIBRARIES( cyclopts dl ${LIBS} )
