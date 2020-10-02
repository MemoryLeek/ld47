add_executable(PROJECT_BIN
	../extlib/flecs/flecs.c
	main.cpp
	systems/InputSystem.cpp
	Context.cpp
	Ecs.cpp
)

if(APPLE)
	# Don't know why SFML_LIBRARIES isn't properly populated..
	target_link_libraries(PROJECT_BIN sfml-graphics sfml-window sfml-system)
else()
	target_link_libraries(PROJECT_BIN ${SFML_LIBRARIES})
endif()
