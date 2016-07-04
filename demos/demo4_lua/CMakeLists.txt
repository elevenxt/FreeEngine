
cmake_minimum_required(VERSION 2.8)

set(PROJ_NAME demo4_lua)
file(GLOB SRCLIST ./src/*.*)

link_directories(${THIRDLIB_DIR}/LuaJIT-2.0.4/src)

add_executable(${PROJ_NAME} ${SRCLIST})

include_directories(
	./src/
	${BASE_DIR}/src
	${LAUNCHER_DIR}/src
	${THIRDLIB_DIR}/cppformat-master
	${MODULE_DIR}/modulelua/src
	${THIRDLIB_DIR}/lua-5.3.3/src
	)

target_link_libraries(${PROJ_NAME} 
	base
	launcher
	cppformat
	modulelua
	lua
	)

set_target_properties(${PROJ_NAME} PROPERTIES FOLDER "advanced.demo") 