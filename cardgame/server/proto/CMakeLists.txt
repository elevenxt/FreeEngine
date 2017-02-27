
cmake_minimum_required(VERSION 2.8)

set(PROJ_NAME card_game_proto)
file(GLOB SRCLIST ./*.h ./*.cpp ./*.cc)

include_directories( 
	${BASE_DIR}/src
	${THIRDLIB_DIR}/protobuf-master/src
)

add_library(${PROJ_NAME} ${SRCLIST})

target_link_libraries(${PROJ_NAME}
	protobuf
)

set_target_properties(${PROJ_NAME} PROPERTIES FOLDER "game.card")
