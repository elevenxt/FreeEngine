
cmake_minimum_required(VERSION 2.8)

set(PROJ_NAME demo5_netserver)
file(GLOB SRCLIST ./src/*.*)

add_executable(${PROJ_NAME} ${SRCLIST})

include_directories(
	./src/
	${BASE_DIR}/src
	${LAUNCHER_DIR}/src
	${THIRDLIB_DIR}/cppformat-master
	${MODULE_DIR}/modules/src
	${THIRDLIB_DIR}/ut/lib
	)

IF(WIN32)
	set(ws2_32 ws2_32)
ELSEIF(UNIX)
	set(dl dl)
	set(pthread pthread)
ENDIF(WIN32)

target_link_libraries(${PROJ_NAME} 
	base
	launcher
	cppformat
	modules
	ut
	${ws2_32}
	${dl}
	${pthread}
	)

set_target_properties(${PROJ_NAME} PROPERTIES FOLDER "advanced.demo") 