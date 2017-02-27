
cmake_minimum_required(VERSION 2.8)

set(PROJ_NAME deps)

file(GLOB LZ4 lz4-master/lib/*.h lz4-master/lib/*.c)
add_library(lz4 ${LZ4})

file(GLOB INIPARSER iniparser-master/src/*.h iniparser-master/src/*.c)
add_library(iniparser ${INIPARSER})

add_subdirectory("cppformat-master")
add_subdirectory("protobuf-master")
add_subdirectory("rocksdb-master")
add_subdirectory("lua-5.3.3")
add_subdirectory("ut")
