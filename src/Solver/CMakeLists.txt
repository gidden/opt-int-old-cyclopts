# Add any new core source files to this list.
SET( CYCLOPTS_SRC ${CYCLOPTS_SRC} 
  ${CMAKE_CURRENT_SOURCE_DIR}/CyclusSolver.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/CBCSolver.cpp
  PARENT_SCOPE)

# add include files
SET( CYCLOPTS_INCL ${CYCLOPTS_INCL} 
  ${CMAKE_CURRENT_SOURCE_DIR}/CyclusSolver.h
  ${CMAKE_CURRENT_SOURCE_DIR}/CBCSolver.h
  PARENT_SCOPE)
