cmake_minimum_required(VERSION 3.20)
project(shell_game_engine)

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)  # Includes the contents of the conanbuildinfo.cmake file.
conan_basic_setup()  # Prepares the CMakeList.txt for Conan.

include_directories("src")

add_executable(shell_game_engine src/main.cpp src/Engine/Core/Logger.cpp src/Engine/Core/Logger.h)

# $source_files is a space-delimited list of filenames.
target_link_libraries(shell_game_engine ${CONAN_LIBS})  # Specifies what libraries to link, using Conan.
