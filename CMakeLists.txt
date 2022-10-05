set(project KirbyAdventure)

set(USING_ECLIPSE FALSE CACHE BOOL "")

project(${project})

# CMake 3.4 come suggerito da CMake
cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

# Raccolta sorgenti
# Il file globbing è sconsigliato dalla documentazione. Serve una nuova soluzione
# file(GLOB sorgenti *.h *.cpp *.qrc)
# La soluzione è questa: Per ogni file
# In Caso di set in subdirectory: # set(sorgenti "${sorgenti}${CMAKE_CURRENT_SOURCE_DIR}/main.cpp " PARENT_SCOPE)
# In questo file:
set(sorgenti "main.cpp;MainWindow.cpp;MainWindow.h")
message(STATUS "${sorgenti}")

# Includi una directory (placeholder per quando servirà)
# add_subdirectory("src")

# Imposto standard C++17 richiesto da Qt e flags per fermare la build al primo errore
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(${USING_ECPLISE})
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -pedantic -Wfatal-errors")
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

# Richiesto dalla documentazione
qt_standard_project_setup()

# Collego librerie Qt con eseguibile
target_link_libraries(${project} Qt6::Widgets)
