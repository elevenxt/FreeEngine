
cmake_minimum_required(VERSION 2.8)

set(PROJ_NAME demo1_module)
file(GLOB SRCLIST ./src/*.*)

add_executable(${PROJ_NAME} ${SRCLIST})

include_directories(
	./src/
	${BASE_DIR}/src
	${LAUNCHER_DIR}/src
	${THIRDLIB_DIR}/cppformat-master
	)

target_link_libraries(${PROJ_NAME} 
	base
	launcher
	cppformat
	ut
	${ws2_32}
	${dl}
	${pthread}
	)

set_target_properties(${PROJ_NAME} PROPERTIES FOLDER "basic.demo") 
