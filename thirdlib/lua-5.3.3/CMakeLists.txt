# Copyright (c) 2010-2016 A.W. Stanley.
# This file is released into the public domain.
#
# This file handles the core Lua code.
# It exists because I grew tired messing with things.

# Lua version
set(LUA_VERSION_MAJOR 5 CACHE INTERNAL "" FORCE)
set(LUA_VERSION_MINOR 3 CACHE INTERNAL "" FORCE)
set(LUA_VERSION "${LUA_VERSION_MAJOR}.${LUA_VERSION_MINOR}")

# CMake 3.0 to support msys and other platforms work;
# too high for TravisCI but allows for general use
cmake_minimum_required(VERSION 2.8)

# Project
set(LUA_PROJECT_NAME "Lua ${LUA_VERSION}")
project(${LUA_PROJECT_NAME})

if(NOT DEFINED LUA_SHARED_LIB)
	set(LUA_SHARED_LIB OFF)
endif()
set(LUA_SHARED_LIB ${LUA_SHARED_LIB} CACHE BOOL
	"Build Lua as a shared library"
	FORCE
)

if(NOT DEFINED LUA_BINARY_OUT)
	set(LUA_BINARY_OUT "${CMAKE_CURRENT_BINARY_DIR}/build/bin")
endif()
set(LUA_BINARY_OUT ${LUA_BINARY_OUT} CACHE STRING
	"Path into which the shared library should go (if LUA_SHARED_LIB is set)"
	FORCE
)

if(NOT DEFINED LUA_LIBRARY_OUT)
	set(LUA_LIBRARY_OUT "${CMAKE_CURRENT_BINARY_DIR}/build/lib")
endif()
set(LUA_LIBRARY_OUT ${LUA_LIBRARY_OUT} CACHE STRING
	"Path into which the shared library should go (if LUA_BUILD_BINARIES is set)"
	FORCE
)

if(NOT DEFINED LUA_TOOLS_OUT)
	set(LUA_TOOLS_OUT "${CMAKE_CURRENT_BINARY_DIR}/build/tools")
endif()
set(LUA_TOOLS_OUT ${LUA_TOOLS_OUT} CACHE STRING
	"Path into which the shared library should go (if LUA_BUILD_BINARIES is set)"
	FORCE
)

# Build default Lua binaries
# - Useful for debugging and generally mucking around.
option(LUA_BUILD_BINARIES "Build default Lua binaries (lua and luac)" OFF)

# Include directory
set(LUA_INCLUDE_DIRECTORY
	"${CMAKE_CURRENT_SOURCE_DIR}/src"
	CACHE INTERNAL "" FORCE
)

set(LUA_INC
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lapi.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lauxlib.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lcode.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lctype.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/ldebug.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/ldo.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lfunc.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lgc.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/llex.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/llimits.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lmem.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lobject.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lopcodes.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lparser.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lprefix.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lstate.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lstring.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/ltable.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/ltm.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lua.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/luaconf.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lualib.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lundump.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lvm.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lzio.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lua.hpp"
)

SET(LUA_SRC
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lapi.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lauxlib.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lbaselib.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lbitlib.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lcode.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lcorolib.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lctype.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/ldblib.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/ldebug.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/ldo.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/ldump.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lfunc.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lgc.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/linit.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/liolib.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/llex.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lmathlib.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lmem.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/loadlib.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lobject.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lopcodes.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/loslib.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lparser.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lstate.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lstring.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lstrlib.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/ltable.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/ltablib.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/ltm.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lundump.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lutf8lib.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lvm.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/lzio.c"
)

set(LUA_LIBTYPE STATIC)
if(LUA_SHARED_LIB)
	set(LUA_LIBTYPE SHARED)
endif()
add_library(lua ${LUA_LIBTYPE} ${LUA_INC} ${LUA_SRC})

# Build binaries (lua, luac)
if(LUA_BUILD_BINARIES)

	# lua[.exe]
	add_executable(lua_interpreter
		${LUA_INC}
		"${CMAKE_CURRENT_SOURCE_DIR}/src/lua.c"
	)

	# luac[.exe]
	add_executable(lua_compiler ${LUA_INC} ${LUA_SRC}
		"${CMAKE_CURRENT_SOURCE_DIR}/src/luac.c"
	)

	# Dependencies
	add_dependencies(lua_interpreter lua)

	# Link libraries
	target_link_libraries(lua_interpreter lua)

	if(LUA_SHARED_LIB)
		set_target_properties(lua_interpreter
			PROPERTIES COMPILE_DEFINITIONS
			"LUA_BUILD_AS_DLL"
		)
	endif()
endif()

source_group("Lua\\inc" FILES ${LUA_INC})
source_group("Lua\\src" FILES ${LUA_SRC})

# Lua (lib)
if(LUA_SHARED_LIB)
	set_target_properties(lua
		PROPERTIES COMPILE_DEFINITIONS
		"LUA_BUILD_AS_DLL;LUA_CORE"
	)
else()
	set_target_properties(lua
		PROPERTIES COMPILE_DEFINITIONS
		"LUA_CORE"
	)
endif()
set_target_properties(lua PROPERTIES OUTPUT_NAME "lua${LUA_VERSION}"
	VERSION ${LUA_VERSION} SOVERSION ${LUA_VERSION}
	POSITION_INDEPENDENT_CODE ON
	FOLDER "Lua" 
)

# Build binaries (lua, luac)
if(LUA_BUILD_BINARIES)
	# Lua (compiler)
	set_target_properties(lua_compiler PROPERTIES OUTPUT_NAME luac
		VERSION ${LUA_VERSION} SOVERSION ${LUA_VERSION}
		POSITION_INDEPENDENT_CODE ON
		FOLDER "Lua"
	)

	# Lua (interpreter)
	set_target_properties(lua_interpreter PROPERTIES OUTPUT_NAME lua
		VERSION ${LUA_VERSION} SOVERSION ${LUA_VERSION}
		POSITION_INDEPENDENT_CODE ON
		FOLDER "Lua"
	)
endif()

# Global Lua library
set(LUA_LIBRARY
	lua
	CACHE INTERNAL "" FORCE
)

# This is typically used in my build process.
install(TARGETS lua
	RUNTIME DESTINATION ${LUA_BINARY_OUT}
	LIBRARY DESTINATION ${LUA_LIBRARY_OUT}
	ARCHIVE DESTINATION ${LUA_LIBRARY_OUT})

# Build binaries (lua, luac)
if(LUA_BUILD_BINARIES)
	install(TARGETS lua lua_interpreter lua_compiler
		RUNTIME DESTINATION ${LUA_TOOLS_OUT}
		LIBRARY DESTINATION ${LUA_LIBRARY_OUT}
		ARCHIVE DESTINATION ${LUA_LIBRARY_OUT})
endif()

# Root level (notify)
if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
	message("${PROJECT_NAME} is root")
endif()