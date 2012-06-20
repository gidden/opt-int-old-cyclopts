cmake_minimum_required (VERSION 2.8)

# This project name is cyclopts.
project (APP)

# Direct any out-of-source builds to this directory
SET( APP_SRC_DIR ${CMAKE_SOURCE_DIR} )

# set module path
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)

SET(APP_EXECUTABLE_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Add any new core source files to this list.
SET( APP_SRC App.cpp )

# find coin and link to it
FIND_PACKAGE( CYCLOPTS REQUIRED )
SET(APP_INCLUDE_DIR ${APP_INCLUDE_DIR} ${CYCLOPTS_INCLUDE_DIR})
MESSAGE("\tFound CYCLOPTS Include Dir: ${CYCLOPTS_INCLUDE_DIR}")
set(LIBS ${LIBS} ${CYCLOPTS_LIBRARY})
MESSAGE("\tFound CYCLOPTS Libraries: ${CYCLOPTS_LIBRARY}")

# include all the directories we just found
INCLUDE_DIRECTORIES( ${APP_INCLUDE_DIR} )

# Build the app library from the APP_SRC source files
ADD_LIBRARY( app ${APP_SRC} )
TARGET_LINK_LIBRARIES( app dl ${LIBS} )