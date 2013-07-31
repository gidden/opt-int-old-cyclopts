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

# Add any new core source files to this list.
SET( CYCLOPTS_SRC 
  ${CMAKE_CURRENT_SOURCE_DIR}/solver_interface.cc  
  ${CMAKE_CURRENT_SOURCE_DIR}/solver.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/cbc_solver.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/variable.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/function.cc
  )

# Add any new core source files to this list.
SET( CYCLOPTS_INCL 
  ${CMAKE_CURRENT_SOURCE_DIR}/solver_interface.h
  ${CMAKE_CURRENT_SOURCE_DIR}/solver.h
  ${CMAKE_CURRENT_SOURCE_DIR}/cbc_solver.h
  ${CMAKE_CURRENT_SOURCE_DIR}/solver_tools.h
  ${CMAKE_CURRENT_SOURCE_DIR}/variable.h
  ${CMAKE_CURRENT_SOURCE_DIR}/function.h
  ${CMAKE_CURRENT_SOURCE_DIR}/cyclopts_limits.h
  )

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

# # Include the boost header files
set(Boost_USE_STATIC_LIBS       OFF)
set(Boost_USE_STATIC_RUNTIME    OFF)
FIND_PACKAGE( Boost REQUIRED)
SET(CYCLOPTS_INCLUDE_DIR ${CYCLOPTS_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})
 
# include all the directories we just found
INCLUDE_DIRECTORIES( ${CYCLOPTS_INCLUDE_DIR} )

# set the install name target (for OSX) 
set(CMAKE_INSTALL_NAME_DIR ${CMAKE_INSTALL_PREFIX}/lib)

# Build the cyclopts library from the CYCLOPTS_SRC source files
ADD_LIBRARY( cyclopts ${CYCLOPTS_SRC} )
TARGET_LINK_LIBRARIES( cyclopts ${CMAKE_DL_LIBS} ${LIBS} )

#install the files
install(TARGETS cyclopts DESTINATION lib)
install(FILES ${CYCLOPTS_INCL} DESTINATION include/cyclopts)

# uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/Config/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
