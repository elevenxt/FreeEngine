
cmake_minimum_required(VERSION 2.8)

set(PROJ_NAME modules)
file(GLOB SRCLIST ./src/*.*)

add_library(${PROJ_NAME} STATIC ${SRCLIST})

include_directories(
	./src/interface
	${BASE_DIR}/src
	${MODULE_DIR}/common
	${THIRDLIB_DIR}/cppformat-master
	${THIRDLIB_DIR}/spdlog-master/include/spdlog
	${THIRDLIB_DIR}/rocksdb-master/include
	${THIRDLIB_DIR}/ut/lib
)

IF(WIN32)
	set(rocksdblib rocksdblib)
ELSEIF(UNIX)
	set(rocksdblib rocksdb)
ENDIF(WIN32)

target_link_libraries(${PROJ_NAME} 
	${rocksdblib}
	)

set_target_properties(${PROJ_NAME} PROPERTIES FOLDER "modules")
