cmake_minimum_required(VERSION 3.10.0)
project(engine VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(engine main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# GLFW setup
set(OpenGL_GL_PREFERENCE GLVND)
add_subdirectory(dependencies/glfw)
target_include_directories(${PROJECT_NAME} PUBLIC dependencies/glfw/include)
target_link_libraries(${PROJECT_NAME} glfw)
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)