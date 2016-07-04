
cmake_minimum_required(VERSION 2.8)

set(PROJ_NAME base)
file(GLOB SRCLIST ./src/*.*)

add_library(${PROJ_NAME} ${SRCLIST})

include_directories(
	${THIRDLIB_DIR}/cppformat-master
)

set_target_properties(${PROJ_NAME} PROPERTIES FOLDER "core")
