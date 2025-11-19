cmake_minimum_required(VERSION 3.10)

project (sugar_rush LANGUAGES CXX)

find_package(SFML COMPONENTS Graphics Audio System)

add_executable(main)

target_sources(main
    PRIVATE
        src/main.cpp
)

target_link_libraries(main SFML::Graphics)