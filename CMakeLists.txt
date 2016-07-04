
cmake_minimum_required(VERSION 2.8)

project(ffserver)

set(CMAKE_BUILD_TYPE Debug)

if(UNIX)
set(CMAKE_C_FLAGS_DEBUG		"-Wall -g -pg")
set(CMAKE_C_FLAGS_RELEASE	"-Wall -o4")
set(CMAKE_CXX_FLAGS_DEBUG	"-std=c++11 -Wall -g -pg")
set(CMAKE_CXX_FLAGS_RELEASE	"-std=c++11 -Wall -o4")
ELSEIF(WIN32)
add_definitions(-W2)
endif(UNIX)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(THIRDLIB_DIR ${PROJECT_SOURCE_DIR}/thirdlib)
set(MODULE_DIR ${PROJECT_SOURCE_DIR}/module)
set(BASE_DIR ${PROJECT_SOURCE_DIR}/base)
set(LAUNCHER_DIR ${PROJECT_SOURCE_DIR}/launcher)
set(ACTOR_DIR ${PROJECT_SOURCE_DIR}/actor)
set(PROTO_DIR ${PROJECT_SOURCE_DIR}/protos)

set(MODULE_LINK_DIRECTORIES
	${THIRDLIB_DIR}/LuaJIT-2.0.4/src
	${THIRDLIB_DIR}/lib/protobuf
)

set(MODULE_INCLUDE_DIRECTORIES
	${BASE_DIR}/src
	${THIRDLIB_DIR}/ut/lib
	${THIRDLIB_DIR}/cppformat-master
	${THIRDLIB_DIR}/spdlog-master/include/spdlog	
	${THIRDLIB_DIR}/rapidjson-master/include
	${LAUNCHER_DIR}/src

	${MODULE_DIR}/modulelua/src
	${MODULE_DIR}/modulenetservice/src
	${MODULE_DIR}/modulevar/src
	
	${THIRDLIB_DIR}/LuaJIT-2.0.4/src
	${THIRDLIB_DIR}/protobuf-master/src
	${PROTO_DIR}/code
)

set(MODULE_LINK_LIBRARIES
	lua51
	ut
	base
	launcher
	protos
	protobuf
	cppformat

	modulelua
	modulenetservice

	ws2_32
)

set_property(GLOBAL PROPERTY USE_FOLDERS On)

add_subdirectory(launcher)
add_subdirectory(thirdlib)
add_subdirectory(base)
add_subdirectory(module)
add_subdirectory(demos)

