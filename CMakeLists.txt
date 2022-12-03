set(project KirbyAdventure)

set(USING_ECLIPSE FALSE CACHE BOOL "")
set(CMAKE_VS_INCLUDE_INSTALL_TO_DEFAULT_BUILD 1)

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
else()
	include_directories(${VULKAN_INCLUDE_DIR})
endif()

# Richiedo librerie Qt
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)
find_package(Qt6 REQUIRED COMPONENTS Multimedia)

# Richiesto dalla documentazione
qt_standard_project_setup()

# Collega la cartella con le sprite al progetto altrimenti non si possono vedere le sprite
file(CREATE_LINK "${PROJECT_SOURCE_DIR}/sprites"
        "${CMAKE_CURRENT_BINARY_DIR}/sprites" SYMBOLIC)

# Collega la cartella con i suoni al progetto
file(CREATE_LINK "${PROJECT_SOURCE_DIR}/sounds"
        "${CMAKE_CURRENT_BINARY_DIR}/sounds" SYMBOLIC)

# Collega la cartella con i livelli al progetto
file(CREATE_LINK "${PROJECT_SOURCE_DIR}/levels"
        "${CMAKE_CURRENT_BINARY_DIR}/levels" SYMBOLIC)

# Aggiungo eseguibile
add_executable(${project} ${sorgenti})
# Seleziona startup project per visual studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${project})


# Collego librerie Qt e Vulkan con eseguibile
target_link_libraries(${project} Qt6::Widgets Qt6::OpenGLWidgets Qt6::Multimedia ${VULKAN_LIBRARY})

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
		Sprites.h
		Sprites.cpp
		Camera.h
		Camera.cpp
		Definitions.h
		RenderableObject.h
		TickableObject.h
		GameObject.cpp
		GameObject.h
		Terrain.h
		Serializable.h
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
		Particle.cpp
		ObjectsHolder.h
		Sounds.cpp
		Sounds.h
		Hud.cpp
		Hud.h
		Enemy.cpp
		Enemy.h
		Door.h
		Door.cpp
		NetworkElement.h
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


install(TARGETS ${project} RUNTIME DESTINATION bin)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/sounds/" DESTINATION bin/sounds)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/sprites/" DESTINATION bin/sprites)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/design/" DESTINATION bin/design)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/levels/" DESTINATION bin/levels)
#install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/deployablefiles/" DESTINATION bin)

find_file(QtCore Qt6Core.dll HINTS ENV)
find_file(QtOpenGlWidget Qt6OpenGLWidgets.dll HINTS ENV)
find_file(QtMultim Qt6Multimedia.dll HINTS ENV)
find_file(QtGUI Qt6Gui.dll HINTS ENV)
find_file(QtWidget Qt6Widgets.dll HINTS ENV)
find_file(QtNetwork Qt6Network.dll HINTS ENV)
find_file(QtOpenGL Qt6OpenGL.dll HINTS ENV)

message("${QtCore}")
message("${QtOpenGlWidget}")
message("${QtMultim}")
message("${QtGUI}")
message("${QtWidget}")
message("${QtNetwork}")
message("${QtOpenGL}")

#install(FILES ${PROJECT}
#  ${QtCore} DESTINATION bin
# )

#install(TARGETS ${PROJECT}
#    BUNDLE  DESTINATION .
#    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#)

#qt_generate_deploy_app_script(
#    TARGET ${PROJECT}
#    FILENAME_VARIABLE deploy_script
#    NO_UNSUPPORTED_PLATFORM_ERROR
#)
#install(SCRIPT ${deploy_script})


include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_PACKAGE_VERSION_MAJOR "1.0")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_SOURCE_GENERATOR "TGZ")
include(CPack)
