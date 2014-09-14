cmake_minimum_required(VERSION 2.8)

set (PROJECT Arkanoid)

set ("${PROJECT}_BINARY_DIR" bin)
set ("${PROJECT}_SOURCE_DIR" src)
set ("${PROJECT}_INCLUDE_DIR" include)
set ("${PROJECT}_LIB_DIR" lib)

message ("include dir: ${${PROJECT}_INCLUDE_DIR}")

add_subdirectory (src)

set (MAIN_SOURCES
	game.cpp
)

include_directories ("${${PROJECT}_INCLUDE_DIR}")

INCLUDE(FindPkgConfig)

#find_package (SDL REQUIRED)
find_package (GLU REQUIRED)

include_directories (/usr/include/SDL2/)
include_directories (/usr/lib/i386-linux-gnu/)

add_executable (
	${PROJECT}
	"${${PROJECT}_SOURCE_DIR}/${MAIN_SOURCES}"
)

target_link_libraries (
	${PROJECT}
	game
	${GLU_LIBRARY}
	SDL2
)

