cmake_minimum_required(VERSION 3.10.0)
project(glad VERSION 0.1.0)

# Main library
add_library(${PROJECT_NAME} src/glad.c include/glad/glad.h)
target_include_directories(${PROJECT_NAME} PUBLIC include/)