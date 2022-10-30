set(project KirbyAdventure)

set(USING_ECLIPSE FALSE CACHE BOOL "")

project(${project})

# CMake 3.4 come suggerito da CMake
cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

#if(POLICY CMP0076)
#    cmake_policy(SET CMP0076 NEW)
#endif()

# Hey CMake. Cerca Vulkan.
find_package(Vulkan)

# Avviso se non trovo Vulkan SDK
if(NOT ${VULKAN_FOUND})
	message("Devi installare ed impostare la variabile di sistema VULKAN_SDK")
endif()

# Richiedo librerie Qt
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)

# Richiesto dalla documentazione
qt_standard_project_setup()

# Collega la cartella con le sprite al progetto altrimenti non si possono vedere le sprite
file(CREATE_LINK "${PROJECT_SOURCE_DIR}/sprites"
        "${CMAKE_CURRENT_BINARY_DIR}/sprites" SYMBOLIC)

# Collega la cartella con i suoni al progetto
file(CREATE_LINK "${PROJECT_SOURCE_DIR}/Kirby's Adventure (NES) Sounds"
        "${CMAKE_CURRENT_BINARY_DIR}/Kirby's Adventure (NES) Sounds" SYMBOLIC)

# Aggiungo eseguibile
add_executable(${project} ${sorgenti})

# Collego librerie Qt con eseguibile
target_link_libraries(${project} Qt6::Widgets Qt6::OpenGLWidgets)

# Raccolta sorgenti
# Il file globbing è sconsigliato dalla documentazione. Serve una nuova soluzione
# file(GLOB sorgenti *.h *.cpp *.qrc)
# La soluzione è questa: 
target_sources(${project}
	PRIVATE
		main.cpp
)
target_sources(${project}
	PRIVATE
		MainWindow.cpp
		MainWindow.h
		GameLoop.cpp
		GameLoop.h
		GraphicsScene.h
		GraphicsScene.cpp
		TextureManager.h
		TextureManager.cpp
		Camera.h
		Camera.cpp
		Definitions.h
		RenderableObject.h
		TickableObject.h
		GameObject.cpp
		GameObject.h
		Terrain.h
		Serializable.h
		Serializable.cpp
		RigidBody.cpp
		RigidBody.h
		Animator.h
		Animator.cpp
		CollisionDetection.h
		CollisionDetection.cpp
		Vec2D.h
		Direction.h
		Kirby.h
		Kirby.cpp
		Particle.h
)


# Aggiungi una subdirectory
#add_subdirectory(classes)

# Imposto standard C++17 richiesto da Qt e flags per fermare la build al primo errore
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
if(${USING_ECPLISE})
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wfatal-errors")
endif()

# Attivo funzionalita' specifiche di CMake per Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Suggerito dal compilatore
set(SKIP_AUTOMOC ON)


