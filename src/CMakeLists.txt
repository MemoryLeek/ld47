add_executable(PROJECT_BIN
	../extlib/flecs/flecs.c
	main.cpp
	systems/EventSystem.cpp
	systems/InputSystem.cpp
	systems/MovementSystem.cpp
	Context.cpp
	Ecs.cpp
)

if(APPLE)
	# Don't know why SFML_LIBRARIES isn't properly populated..
	target_link_libraries(PROJECT_BIN sfml-graphics sfml-window sfml-system)
else()
	target_link_libraries(PROJECT_BIN ${SFML_LIBRARIES} -lsfml-window -lsfml-system -lsfml-graphics)
endif()
