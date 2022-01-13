cmake_minimum_required( VERSION 2.6 )

project(main)

# Gebraucht werden OpenGL und GLUT
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# Definition der Headerdateien
set(HEADERS
	./Engine/Collision.hpp
	./Engine/Game.hpp
	./Engine/InputManager.hpp
	./Engine/Parallel.hpp
	./Engine/TextureManager.hpp
	./Engine/util.hpp
	./Engine/Vector2D.hpp
	./Engine/ECS/ColliderComponent.hpp
	./Engine/ECS/ComponentsComponent.hpp
	./Engine/ECS/ECSComponent.hpp
	./Engine/ECS/KeyboardController.hpp
	./Engine/ECS/MarchingSquaresComponent.hpp
	./Engine/ECS/SpirteComponent.hpp
	./Engine/ECS/TileComponent.hpp
	./Engine/ECS/TransformComponent.hpp
	./qdbmp/include/qdbmp.h
)
   
# Definition der Sourcedateien
set(SOURCES
	./Engine/Collision.cpp
	./Engine/Game.cpp
	./Engine/InputManager.cpp
	./Engine/TextureManager.cpp
	./Engine/Vector2D.cpp
	../../dependencies/qdbmp/src/qdbmp.cpp
)

# Includeverzeichnisse setzen
include_directories(
    ./Engine/
	./qdbmp/include
)


# Support fuer C++-11 aktivieren
set(CMAKE_CXX_FLAGS "-std=c++11")

# Ziel hinzufuegen
add_executable(main
    ${SOURCES}
    ${HEADERS}
)

# Bibliotheken linken
target_link_libraries(main ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
