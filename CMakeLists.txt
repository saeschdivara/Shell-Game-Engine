cmake_minimum_required(VERSION 3.20)
project(shell_game_engine)

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)  # Includes the contents of the conanbuildinfo.cmake file.
conan_basic_setup()  # Prepares the CMakeList.txt for Conan.

include_directories("src")

find_package(PkgConfig REQUIRED)
pkg_check_modules(mono-2 REQUIRED mono-2)

add_executable(shell_game_engine
        src/main.cpp
        src/Engine/Core/Logger.cpp src/Engine/Core/Logger.h
        src/Engine/Core/Application.cpp src/Engine/Core/Application.h
        src/Engine/Core/Window.cpp src/Engine/Core/Window.h
        src/Engine/Core/Renderer.cpp src/Engine/Core/Renderer.h
        src/Engine/Core/Utils.h src/Engine/Scripting/ScriptExecutionManager.cpp src/Engine/Scripting/ScriptExecutionManager.h)

# $source_files is a space-delimited list of filenames.
target_link_libraries(shell_game_engine ${CONAN_LIBS})  # Specifies what libraries to link, using Conan.

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    find_package(Backward)

    include_directories("/usr/local/include")
    include_directories("/usr/local/include/mono-2.0")

    # This will add libraries, definitions and include directories needed by backward
    # through an IMPORTED target.
    target_link_libraries(shell_game_engine Backward::Backward)
endif()