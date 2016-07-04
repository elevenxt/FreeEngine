
cmake_minimum_required(VERSION 2.8)

set(PROJ_NAME deps)

file(GLOB LZ4 lz4-master/lib/*.h lz4-master/lib/*.c)
add_library(lz4 ${LZ4})

add_subdirectory("cppformat-master")
add_subdirectory("protobuf-master")
add_subdirectory("lua-5.3.3")
add_subdirectory("ut")


