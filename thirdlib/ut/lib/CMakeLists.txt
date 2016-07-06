
cmake_minimum_required(VERSION 2.8)

set(PROJ_NAME ut)
file(GLOB SRCLIST *.c *.h)

add_library(${PROJ_NAME} ${SRCLIST})

include_directories( "../otherlib/include" )

set_target_properties(${PROJ_NAME} PROPERTIES FOLDER "libs")
