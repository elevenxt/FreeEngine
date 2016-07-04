
cmake_minimum_required(VERSION 2.8)

set(PROJ_NAME demo3_modules)
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
	)

set_target_properties(${PROJ_NAME} PROPERTIES FOLDER "basic.demo") 