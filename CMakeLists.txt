set(project KirbyAdventure)

set(USING_ECLIPSE FALSE CACHE BOOL "")

project(${project})

# CMake 3.4 come suggerito da CMake
cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

file(CREATE_LINK "${PROJECT_SOURCE_DIR}/sprites"
        "${CMAKE_CURRENT_BINARY_DIR}/sprites" SYMBOLIC)

# Raccolta sorgenti
# Il file globbing è sconsigliato dalla documentazione. Serve una nuova soluzione
# file(GLOB sorgenti *.h *.cpp *.qrc)
# La soluzione è questa: Per ogni file
# In Caso di set in subdirectory: # set(sorgenti "${sorgenti}${CMAKE_CURRENT_SOURCE_DIR}/main.cpp " PARENT_SCOPE)
# In questo file:
set(sorgenti "${sorgenti}${CMAKE_CURRENT_SOURCE_DIR}/main.cpp;")
set(sorgenti "${sorgenti}${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.cpp;")
set(sorgenti "${sorgenti}${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.h;")
set(sorgenti "${sorgenti}${CMAKE_CURRENT_SOURCE_DIR}/GameLoop.cpp;")
set(sorgenti "${sorgenti}${CMAKE_CURRENT_SOURCE_DIR}/GameLoop.h;")
set(sorgenti "${sorgenti}${CMAKE_CURRENT_SOURCE_DIR}/GraphicsScene.h;")
set(sorgenti "${sorgenti}${CMAKE_CURRENT_SOURCE_DIR}/GraphicsScene.cpp;")
set(sorgenti "${sorgenti}${CMAKE_CURRENT_SOURCE_DIR}/TextureManager.h;")
set(sorgenti "${sorgenti}${CMAKE_CURRENT_SOURCE_DIR}/TextureManager.cpp;")
set(sorgenti "${sorgenti}${CMAKE_CURRENT_SOURCE_DIR}/Animator.h;")
set(sorgenti "${sorgenti}${CMAKE_CURRENT_SOURCE_DIR}/Animator.cpp;")
set(sorgenti "${sorgenti}${CMAKE_CURRENT_SOURCE_DIR}/GameObject.cpp;")
set(sorgenti "${sorgenti}${CMAKE_CURRENT_SOURCE_DIR}/GameObject.h;")
set(sorgenti "${sorgenti}${CMAKE_CURRENT_SOURCE_DIR}/Serializable.h;")
set(sorgenti "${sorgenti}${CMAKE_CURRENT_SOURCE_DIR}/Serializable.cpp;")
set(sorgenti "${sorgenti}${CMAKE_CURRENT_SOURCE_DIR}/RigidBody.cpp;")
set(sorgenti "${sorgenti}${CMAKE_CURRENT_SOURCE_DIR}/RigidBody.h;")
set(sorgenti "${sorgenti}${CMAKE_CURRENT_SOURCE_DIR}/Camera.h;")
set(sorgenti "${sorgenti}${CMAKE_CURRENT_SOURCE_DIR}/Camera.cpp;")
set(sorgenti "${sorgenti}${CMAKE_CURRENT_SOURCE_DIR}/Terrain.h;")
set(sorgenti "${sorgenti}${CMAKE_CURRENT_SOURCE_DIR}/Vector.cpp;")
set(sorgenti "${sorgenti}${CMAKE_CURRENT_SOURCE_DIR}/Vector.h;")
set(sorgenti "${sorgenti}${CMAKE_CURRENT_SOURCE_DIR}/Definitions.h;")
set(sorgenti "${sorgenti}${CMAKE_CURRENT_SOURCE_DIR}/Kirby.cpp;")
set(sorgenti "${sorgenti}${CMAKE_CURRENT_SOURCE_DIR}/Kirby.h;")
# set(sorgenti "${sorgenti}${CMAKE_CURRENT_SOURCE_DIR}/;")


message(STATUS "${sorgenti}")

# Includi una directory (placeholder per quando servirà)
# add_subdirectory("src")
add_subdirectory("objects")

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

# Aggiungo eseguibile
add_executable(${project} ${sorgenti})

# Richiedo librerie Qt
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)


# Richiesto dalla documentazione
qt_standard_project_setup()

# Collego librerie Qt con eseguibile
target_link_libraries(${project} Qt6::Widgets Qt6::OpenGLWidgets)
