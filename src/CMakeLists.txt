# Semi-ghetto way to build tmxlite.. Can't figure out ExternalProject_Add for static libs..
include_directories(${CMAKE_SOURCE_DIR}/extlib/tmxlite/tmxlite/include)
set(PROJECT_DIR ${CMAKE_SOURCE_DIR}/extlib/tmxlite/tmxlite/src)
include(${PROJECT_DIR}/CMakeLists.txt)

add_executable(${PROJECT_BIN}
	${PROJECT_SRC}
	${CMAKE_SOURCE_DIR}/extlib/flecs/flecs.c
	main.cpp
	graphics/AnimatedSprite.cpp
	graphics/Animation.cpp
	systems/EventSystem.cpp
	systems/InputSystem.cpp
	systems/MovementSystem.cpp
	systems/TileLayerRenderingSystem.cpp
	systems/PlayerAnimationSystem.cpp
	graphics/AnimatedSprite.cpp
	graphics/Animation.cpp
	Context.cpp
	Ecs.cpp
	MapLoader.cpp
)

if(APPLE)
	# Don't know why SFML_LIBRARIES isn't properly populated..
	target_link_libraries(${PROJECT_BIN} sfml-graphics sfml-window sfml-system)
else()
	target_link_libraries(${PROJECT_BIN} ${SFML_LIBRARIES} -lsfml-window -lsfml-system -lsfml-graphics)
endif()

# Copy assets to build directory
add_custom_command(TARGET ${PROJECT_BIN} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_BIN}>/assets
)
