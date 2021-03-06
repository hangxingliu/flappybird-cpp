cmake_minimum_required(VERSION 2.8)

project(flappy-bird-sdl2)

set(TARGET_NAME "flappy-bird")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -std=c++11")

FILE(GLOB_RECURSE HEADER_FILES "./src/*.h")
add_executable(${TARGET_NAME}
	src/main.cc
	src/utils.cc
	${HEADER_FILES})

# Fix MacOSX pkg-config
if(APPLE)
	link_directories(/usr/local/lib)
	set(CMAKE_MACOSX_RPATH 1)
	set(ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:/usr/local/lib/pkgconfig:/opt/X11/lib/pkgconfig")
endif()

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

INCLUDE_DIRECTORIES(
	${SDL2_INCLUDE_DIRS}
	${SDL2IMAGE_INCLUDE_DIRS}
	${SDL2TTF_INCLUDE_DIRS})

TARGET_LINK_LIBRARIES(
	${TARGET_NAME}
	${SDL2_LIBRARIES}
	${SDL2IMAGE_LIBRARIES}
	${SDL2TTF_LIBRARIES})
