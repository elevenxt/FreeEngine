
cmake_minimum_required(VERSION 2.8)

set(PROJ_NAME moduleactor)
file(GLOB SRCLIST ./src/*.*)

add_library(${PROJ_NAME} ${SRCLIST})

include_directories(
	${BASE_DIR}/src
	${MODULE_DIR}/common
	${THIRDLIB_DIR}/cppformat-master
	${THIRDLIB_DIR}/spdlog-master/include/spdlog
)

set_target_properties(${PROJ_NAME} PROPERTIES FOLDER "modules") 