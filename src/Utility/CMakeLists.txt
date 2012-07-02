# Add any new core source files to this list.
SET( CYCLOPTS_SRC ${CYCLOPTS_SRC} 
  ${CMAKE_CURRENT_SOURCE_DIR}/Variable.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Function.cpp
  PARENT_SCOPE)

#add include files
SET( CYCLOPTS_INCL ${CYCLOPTS_INCL} 
  ${CMAKE_CURRENT_SOURCE_DIR}/SolverTools.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Variable.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Function.h
  PARENT_SCOPE)
