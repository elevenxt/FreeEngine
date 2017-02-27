
cmake_minimum_required(VERSION 2.8)

set(PROJ_NAME card_game_frame)
file(GLOB SRCLIST ./src/*.* ./src/interface/*.*)

add_executable(${PROJ_NAME} ${SRCLIST})

include_directories(
	./src/
	./src/interface
	../proto
	${BASE_DIR}/src
	${LAUNCHER_DIR}/src
	${THIRDLIB_DIR}/ut/lib
	${THIRDLIB_DIR}/iniparser-master/src
	${THIRDLIB_DIR}/cppformat-master
	${THIRDLIB_DIR}/protobuf-master/src
	${THIRDLIB_DIR}/rocksdb-master/include
	${MODULE_DIR}/modules/src
	)

IF(WIN32)
	set(rocksdblib rocksdblib)
ELSEIF(UNIX)
	set(rocksdblib rocksdb)
ENDIF(WIN32)

target_link_libraries(${PROJ_NAME} 
	ut
	base
	launcher
	cppformat
	protobuf
	${rocksdblib}
	iniparser
	modules
	card_game_proto
	${ws2_32}
	${dl}
	${pthread}
	)

set_target_properties(${PROJ_NAME} PROPERTIES FOLDER "game.card")
SET_TARGET_PROPERTIES(card_game_frame PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${ROOT_DIR}/bin/cardgame) 

