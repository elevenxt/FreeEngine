
cmake_minimum_required(VERSION 2.8)

set(PROJ_NAME demo6_actor)

file(GLOB SRCLIST ./src/*.*)

add_executable(${PROJ_NAME} ${SRCLIST})

include_directories(
	./src/
	${BASE_DIR}/src
	${LAUNCHER_DIR}/src
	${THIRDLIB_DIR}/cppformat-master
	${MODULE_DIR}/moduleactor/src
	)

IF(UNIX)
	set(dl dl)
	set(pthread pthread)
ENDIF(UNIX)

target_link_libraries(${PROJ_NAME} 
	base
	launcher
	cppformat
	moduleactor
	${dl}
	${pthread}
	)

set_target_properties(${PROJ_NAME} PROPERTIES FOLDER "advanced.demo") 