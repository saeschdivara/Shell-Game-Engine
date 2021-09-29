cmake_minimum_required(VERSION 3.20)
project(shell_game_engine_editor)

add_executable(shell_editor
    src/main.cpp
)

target_link_libraries(shell_editor shell_game_engine)