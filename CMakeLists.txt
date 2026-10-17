cmake_minimum_required(VERSION 3.20)
project(tictac LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Lets editors/tools (IntelliSense, clangd) see the exact compile flags.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(tictac
    src/main.cpp
    src/board.cpp
    src/player.cpp
    src/engine.cpp
)

target_compile_options(tictac PRIVATE -Wall -Wextra -Wpedantic)
