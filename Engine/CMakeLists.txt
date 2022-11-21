cmake_minimum_required(VERSION 3.10.0)
project(engine VERSION 0.1.0)

include(CTest)
enable_testing()

# Main library
add_library(${PROJECT_NAME} src/Engine/Application.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC src/)

# GLFW setup
set(OpenGL_GL_PREFERENCE GLVND)
add_subdirectory(vendor/glfw)
target_include_directories(${PROJECT_NAME} PUBLIC vendor/glfw/include/)
target_link_libraries(${PROJECT_NAME} glfw)
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)

# not sure if needed, TODO: read docs
# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)