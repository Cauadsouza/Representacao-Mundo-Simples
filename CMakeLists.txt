cmake_minimum_required(VERSION 3.20)

project(
    representacao_mundo
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

find_package(raylib 5.0 QUIET)

if (NOT raylib_FOUND)
    message(STATUS "raylib nao encontrada no sistema. Baixando com FetchContent...")

    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
        GIT_SHALLOW TRUE
    )

    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(raylib)
endif()

add_executable(
    representacao_mundo
    src/main.cpp
    src/Jogo.cpp
    src/Jogador.cpp
    src/NPC.cpp
    src/Mundo.cpp
)

target_include_directories(
    representacao_mundo
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(
    representacao_mundo
    PRIVATE
    raylib
)

if (UNIX AND NOT APPLE)
    target_link_libraries(
        representacao_mundo
        PRIVATE
        m
        pthread
        dl
        rt
        X11
    )
endif()
