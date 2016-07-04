
cmake_minimum_required(VERSION 2.8)

set(PROJ_NAME modulelua)
file(GLOB SRCLIST ./src/*.*)

add_library(${PROJ_NAME} ${SRCLIST})

include_directories(
	${ACTOR_DIR}/src
	${BASE_DIR}/src
	${MODULE_DIR}/common
	${MODULE_DIR}/modulenetservice/src
	${THIRDLIB_DIR}/ut/lib
	${THIRDLIB_DIR}/cppformat-master
	${THIRDLIB_DIR}/spdlog-master/include/spdlog
	${THIRDLIB_DIR}/lua-5.3.3/src
)

set_target_properties(${PROJ_NAME} PROPERTIES FOLDER "modules") 
