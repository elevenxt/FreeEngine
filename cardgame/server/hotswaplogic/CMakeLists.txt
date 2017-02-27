
cmake_minimum_required(VERSION 2.8)

set(PROJ_NAME card_game_logic)
file(GLOB SRCLIST ./src/*.*)

add_library(${PROJ_NAME} SHARED ${SRCLIST})

include_directories(
	./src/
	../proto
	${BASE_DIR}/src
	${THIRDLIB_DIR}/cppformat-master	
	${THIRDLIB_DIR}/protobuf-master/src
	./../frame/src/interface
	)

target_link_libraries(${PROJ_NAME} 
	base
	cppformat
	protobuf
	card_game_proto
	)

set_target_properties(${PROJ_NAME} PROPERTIES FOLDER "game.card")
SET_TARGET_PROPERTIES(card_game_logic PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${ROOT_DIR}/bin/cardgame) 
SET_TARGET_PROPERTIES(card_game_logic PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${ROOT_DIR}/bin/cardgame) 
