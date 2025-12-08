cmake_minimum_required(VERSION 4.0)
project(particl)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

include_directories(../core)
add_executable(particl main.cpp
        ../core/particl.cpp
        ../core/particl.h
        renderer.cpp
        renderer.h
        ../core/Vector2.cpp
        ../core/vector2.h
)
target_link_libraries(particl PRIVATE SFML::Graphics)
