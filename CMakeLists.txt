set(project Kirby-Tec)

project(${project})

# CMake 3.4.0 come suggerito da CMake
cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

# Raccolta sorgenti
file(GLOB sorgenti *.h *.cpp *.qrc)

# Imposto standard C++17 richiesto da Qt e flags per tagliare gli errori a cascata
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -pedantic -Wfatal-errors")

# Attivo funzionalità specifiche di CMake per Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Suggerito dal compilatore
set(SKIP_AUTOMOC ON)

# Aggiungo eseguibile
add_executable(${project} ${sorgenti})

# Richiedo librerie Qt
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

# Collego librerie Qt con eseguibile
target_link_libraries(${project} Qt6::Core Qt6::Widgets)