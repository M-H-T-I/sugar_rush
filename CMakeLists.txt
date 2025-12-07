cmake_minimum_required(VERSION 3.10)

project (sugar_rush LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

find_package(SFML COMPONENTS Graphics Audio System)

add_executable(main)

target_sources(main
    PRIVATE
        src/main.cpp
        src/TitleScreen.cpp
        src/common.cpp
        src/LvlSelector.cpp
        src/Lvl1.cpp
        src/Lvl2.cpp
        src/Lvl3.cpp
        src/GameUtils.cpp
        src/Settings.cpp
        src/Tutorial.cpp
        src/fileHandler.cpp
)

target_link_libraries(main SFML::Graphics SFML::Window SFML::Audio)