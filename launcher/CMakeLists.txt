
cmake_minimum_required(VERSION 2.8)

set(PROJ_NAME launcher)
file(GLOB SRCLIST ./src/*.*)

add_library(${PROJ_NAME} ${SRCLIST})

include_directories(
	./src
	${BASE_DIR}/src
	${THIRDLIB_DIR}/ut/lib
	${THIRDLIB_DIR}/cppformat-master
	${THIRDLIB_DIR}/spdlog-master/include/spdlog
	${THIRDLIB_DIR}/rapidjson-master/include
)

target_link_libraries(${PROJ_NAME} base)

set_target_properties(${PROJ_NAME} PROPERTIES FOLDER "core") 
