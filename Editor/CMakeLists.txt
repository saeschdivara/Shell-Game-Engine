cmake_minimum_required(VERSION 3.20)
project(shell_game_engine_editor)

include_directories(
    src/
)

add_executable(shell_editor
    src/main.cpp
        src/UI/UILayer.cpp src/UI/UILayer.h
    src/Events/EditorEvents.h
    src/Core/FileDialog.cpp src/Core/FileDialog.h
    src/Project/ProjectSerializer.cpp src/Project/ProjectSerializer.h src/UI/Panel/EntityPropsPanel.cpp src/UI/Panel/EntityPropsPanel.h src/UI/Panel/Panel.h)

target_link_libraries(shell_editor shell_game_engine)
target_link_libraries(shell_editor nfd)
target_link_libraries(shell_editor yaml-cpp)

add_custom_command(
        TARGET shell_editor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Editor/assets
        ${CMAKE_CURRENT_BINARY_DIR}/../bin/assets)
