cmake_minimum_required(VERSION 3.20)
project(shell_game_engine)

set(CMAKE_CXX_STANDARD 20)
set(CONAN_DISABLE_CHECK_COMPILER 1)

add_compile_options("$<$<CONFIG:DEBUG>:-DSHELL_APP_DEBUG>") # define debug symbol when using debug build
add_compile_options("$<$<CONFIG:DEBUG>:-DSHELL_PROFILING>") # define debug symbol when using debug build

# add defines for each platform
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_compile_options("-DSHELL_PLATFORM_WINDOWS")
endif()
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    add_compile_options("-DSHELL_PLATFORM_LINUX")
endif()
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_compile_options("-DSHELL_PLATFORM_MACOS")
endif()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)  # Includes the contents of the conanbuildinfo.cmake file.
conan_basic_setup()  # Prepares the CMakeList.txt for Conan.

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Vendors/ImGui/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Vendors/Glad/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Vendors/Backward/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Vendors/FileDialog/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Vendors/Optick/)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Vendors/Spdlog/)

    include_directories("Vendors/Spdlog/include")
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Vendors/Yaml/)

    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Vendors/Yaml/include")
endif()

include_directories(
        "src"
        "Vendors/ImGui"
        "Vendors/Glad/include"
        "Vendors/Backward"
        "Vendors/Optick/src"
)

set(ENGINE_FILES
    src/Engine/Core/Logger.cpp src/Engine/Core/Logger.h
    src/Engine/Core/Application.cpp src/Engine/Core/Application.h
    src/Engine/Core/Window.cpp src/Engine/Core/Window.h
    src/Engine/Core/Rendering/Renderer.cpp src/Engine/Core/Rendering/Renderer.h
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
    src/Platform/MacOS/MacOSInputService.cpp src/Platform/MacOS/MacOSInputService.h
    src/Engine/Core/Rendering/GraphicsContext.h
    src/Platform/Rendering/OpenGL/OpenGLContext.cpp src/Platform/Rendering/OpenGL/OpenGLContext.h
    src/Engine/Core/Rendering/Shader.h src/Engine/Core/Rendering/Shader.cpp
    src/Engine/Core/Assert.h
    src/Engine/Core/Rendering/Texture.h src/Engine/Core/Rendering/Texture.cpp
    src/Engine/Core/Rendering/Buffer.h src/Engine/Core/Rendering/Buffer.cpp
    src/Platform/Rendering/OpenGL/OpenGLBuffer.cpp src/Platform/Rendering/OpenGL/OpenGLBuffer.h
    src/Engine/Core/Rendering/API.h
    src/Engine/Core/Rendering/BufferContainer.cpp src/Engine/Core/Rendering/BufferContainer.h
    src/Platform/Rendering/OpenGL/OpenGLBufferContainer.cpp src/Platform/Rendering/OpenGL/OpenGLBufferContainer.h
    src/Platform/Rendering/OpenGL/OpenGLRenderCommand.cpp src/Platform/Rendering/OpenGL/OpenGLRenderCommand.h
    src/Engine/Core/Rendering/RenderCommand.cpp src/Engine/Core/Rendering/RenderCommand.h
    src/Engine/Core/Rendering/Camera.h src/Engine/Core/Rendering/Camera.cpp
    src/Platform/Rendering/OpenGL/OpenGLShader.cpp src/Platform/Rendering/OpenGL/OpenGLShader.h
    src/Platform/Rendering/OpenGL/OpenGLTexture.cpp src/Platform/Rendering/OpenGL/OpenGLTexture.h
    src/Engine/lib.h
    src/Engine/Core/Rendering/FrameBuffer.cpp src/Engine/Core/Rendering/FrameBuffer.h
    src/Platform/Rendering/OpenGL/OpenGLFrameBuffer.cpp src/Platform/Rendering/OpenGL/OpenGLFrameBuffer.h
    src/Engine/Project/Project.cpp src/Engine/Project/Project.h
    src/Engine/Project/ProjectSettings.cpp src/Engine/Project/ProjectSettings.h
    src/Engine/Project/Scene.cpp src/Engine/Project/Scene.h
    src/Engine/Project/SceneBlueprint.cpp src/Engine/Project/SceneBlueprint.h
    src/Engine/Project/Entities/EntityManager.cpp src/Engine/Project/Entities/EntityManager.h
    src/Engine/Project/Entities/Components.h
    src/Engine/Project/Entities/SceneEntity.cpp src/Engine/Project/Entities/SceneEntity.h
    src/Engine/Core/Rendering/RenderQueue.cpp src/Engine/Core/Rendering/RenderQueue.h
    src/Engine/Core/Events/EventPublisher.cpp src/Engine/Core/Events/EventPublisher.h
    src/Engine/Core/EngineVersion.h
    src/Engine/Utils/Uuid.cpp src/Engine/Utils/Uuid.h
    src/Engine/Runtime/RuntimeManager.cpp src/Engine/Runtime/RuntimeManager.h
    src/Engine/Scripting/VisualStudioProjectManager.cpp src/Engine/Scripting/VisualStudioProjectManager.h
    src/Engine/Utils/Xml.cpp src/Engine/Utils/Xml.h src/Engine/Runtime/Mono/helpers.h src/Engine/Runtime/Mono/helpers.cpp src/Engine/Core/Profiling.h)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_library(shell_game_engine STATIC ${ENGINE_FILES})
else()
    add_library(shell_game_engine SHARED ${ENGINE_FILES})
endif()

target_precompile_headers(
        shell_game_engine
        PUBLIC src/Engine/Core/shellpch.h
)

target_link_libraries(shell_game_engine ${CONAN_LIBS})  # Specifies what libraries to link, using Conan.
target_link_libraries(shell_game_engine imgui)
target_link_libraries(shell_game_engine glad)
target_link_libraries(shell_game_engine OptickCore)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    target_link_libraries(shell_game_engine spdlog)
endif()

# This will add libraries, definitions and include directories needed by backward
# through an IMPORTED target.
target_link_libraries(shell_game_engine backward)

find_package(PkgConfig REQUIRED)
pkg_check_modules(MONO2 REQUIRED monosgen-2)

target_link_directories(shell_game_engine PUBLIC ${MONO2_LIBRARY_DIRS})

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    target_link_libraries(shell_game_engine mono-2.0-sgen)
else()
    target_link_libraries(shell_game_engine ${MONO2_LINK_LIBRARIES})
endif()

target_include_directories(shell_game_engine PUBLIC ${MONO2_INCLUDE_DIRS})

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_compile_options(shell_game_engine PUBLIC ${MONO2_CFLAGS_OTHER})
endif()

include_directories("/usr/local/include")
include_directories("/usr/local/include/mono-2.0")

########### Example Application ###########

add_executable(shell_sandbox_game
        src/Sandbox/main.cpp
        src/Sandbox/Layers/SampleLayer.h
        src/Sandbox/Layers/RenderLayer.h src/Sandbox/Layers/RenderLayer.cpp)

target_link_libraries(shell_sandbox_game shell_game_engine)

########### Editor Application ###########

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Editor/)