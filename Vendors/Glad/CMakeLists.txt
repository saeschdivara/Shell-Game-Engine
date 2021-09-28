cmake_minimum_required(VERSION 3.20)
project(glad)

include_directories(include)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_library(glad STATIC src/glad.c)
else()
    add_library(glad SHARED src/glad.c)
endif()