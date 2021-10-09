cmake_minimum_required(VERSION 3.20)
project(shell_game_engine_editor)

include_directories(
    src/
)

add_executable(shell_editor
    src/main.cpp
    src/Layers/UILayer.cpp src/Layers/UILayer.h
    src/Events/EditorEvents.h)

target_link_libraries(shell_editor shell_game_engine)

add_custom_command(
        TARGET shell_editor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Editor/assets
        ${CMAKE_CURRENT_BINARY_DIR}/../bin/assets)
