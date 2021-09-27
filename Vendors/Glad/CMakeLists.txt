cmake_minimum_required(VERSION 3.20)
project(glad)

include_directories(include)

add_library(glad SHARED src/glad.c)