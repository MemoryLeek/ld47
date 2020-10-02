cmake_minimum_required(VERSION 3.18)

set(PROJECT_BIN ld47)
project(PROJECT_BIN LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(${SFML_INCLUDE_DIR})
if(APPLE)
	# Don't know why the above isn't enough..
	include_directories(/usr/local/include)
endif()

include_directories(extlib/flecs)

add_subdirectory(src)
