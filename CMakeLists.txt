cmake_minimum_required(VERSION 3.20)
project(shell_game_engine)

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)  # Includes the contents of the conanbuildinfo.cmake file.
conan_basic_setup()  # Prepares the CMakeList.txt for Conan.

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Vendors/ImGui/)

include_directories(
        "src"
        "Vendors/ImGui"
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(MONO2 REQUIRED mono-2)

add_library(shell_game_engine SHARED
        src/Engine/Core/Logger.cpp src/Engine/Core/Logger.h
        src/Engine/Core/Application.cpp src/Engine/Core/Application.h
        src/Engine/Core/Window.cpp src/Engine/Core/Window.h
        src/Engine/Core/Renderer.cpp src/Engine/Core/Renderer.h
        src/Engine/Core/Utils.h
        src/Engine/Scripting/ScriptExecutionManager.cpp src/Engine/Scripting/ScriptExecutionManager.h
        src/Engine/Core/Events/ApplicationEvent.h src/Engine/Core/Events/Event.h
        src/Engine/Core/Events/KeyEvent.h src/Engine/Core/Events/MouseEvent.h src/Engine/Core/Events/GamepadEvent.h
        src/Engine/Core/Events/Codes/MouseCodes.h src/Engine/Core/Events/Codes/KeyCodes.h src/Engine/Core/Events/Codes/GamePadCodes.h
        src/Engine/Core/shellpch.h
        src/Engine/Core/Layers/Layer.cpp src/Engine/Core/Layers/Layer.h
        src/Engine/Core/Layers/LayerStack.cpp src/Engine/Core/Layers/LayerStack.h
        src/Engine/Core/Base.h
        src/Engine/Core/Layers/UiLayer.cpp src/Engine/Core/Layers/UiLayer.h
        src/Engine/UI/imgui_impl_glfw.cpp src/Engine/UI/imgui_impl_glfw.h
        src/Engine/UI/imgui_impl_opengl3.cpp src/Engine/UI/imgui_impl_opengl3.h
        src/Engine/Core/InputService.h
        src/Platform/MacOS/MacOSInputService.cpp src/Platform/MacOS/MacOSInputService.h)

target_precompile_headers(
        shell_game_engine
        PUBLIC src/Engine/Core/shellpch.h
)

target_link_libraries(shell_game_engine ${CONAN_LIBS})  # Specifies what libraries to link, using Conan.
target_link_libraries(shell_game_engine imgui)  # Specifies what libraries to link, using Conan.

target_link_libraries(shell_game_engine ${MONO2_LINK_LIBRARIES})
target_include_directories(shell_game_engine PUBLIC ${MONO2_INCLUDE_DIRS})
target_compile_options(shell_game_engine PUBLIC ${MONO2_CFLAGS_OTHER})

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    find_package(Backward)

    include_directories("/usr/local/include")
    include_directories("/usr/local/include/mono-2.0")

    # This will add libraries, definitions and include directories needed by backward
    # through an IMPORTED target.
    target_link_libraries(shell_game_engine Backward::Backward)
endif()

########### Example Application ###########

add_executable(shell_sandbox_game
        src/Sandbox/main.cpp)

target_link_libraries(shell_sandbox_game shell_game_engine)