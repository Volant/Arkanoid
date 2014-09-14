set (CMAKE_INCLUDE_PATH ${${PROJECT}_SOURCE_DIR})
set (CMAKE_LIB_PATH ${${PROJECT}_LIB_DIR})
set (EXECUTABLE_OUTPUT_PATH ${${PROJECT}_BINARY_DIR})

INCLUDE(FindPkgConfig)

#find_package (SDL REQUIRED)
find_package (GLU REQUIRED)

include_directories (/usr/include/SDL2/)
include_directories (/usr/lib/i386-linux-gnu/)

include_directories ("../${${PROJECT}_INCLUDE_DIR}")

set (SOURCE_LIB
	arkanoid
	image
)

add_library (game STATIC ${SOURCE_LIB})


