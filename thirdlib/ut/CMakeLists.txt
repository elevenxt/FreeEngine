
cmake_minimum_required(VERSION 2.8)

set(PROJ_NAME uttest)

file(GLOB SRCLIST *.c *.h)
add_executable(${PROJ_NAME} ${SRCLIST})

include_directories ("./lib")
include_directories ("../thirdlib/icl")

add_subdirectory(lib)

target_link_libraries(${PROJ_NAME} ut)

if(UNIX)
target_link_libraries(${PROJ_NAME} pthread)
target_link_libraries(${PROJ_NAME} m)
target_link_libraries(${PROJ_NAME} dl)
ELSEIF(WIN32)
target_link_libraries(${PROJ_NAME} ws2_32)
target_link_libraries(${PROJ_NAME} Mswsock)
endif(UNIX)

set_target_properties(${PROJ_NAME} PROPERTIES FOLDER "libs") 
