cmake_minimum_required(VERSION 3.10.0)
project(engineproject VERSION 0.1.0)

include(CTest)
enable_testing()

# Main executable
add_executable(${PROJECT_NAME} Sandbox/src/SandboxApp.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# All subdirectories
add_subdirectory(Engine)
target_link_libraries(${PROJECT_NAME} engine)

# GLFW setup
# set(OpenGL_GL_PREFERENCE GLVND)
# add_subdirectory(Engine/vendor/glfw)
# target_include_directories(${PROJECT_NAME} PUBLIC Engine/vendor/glfw/include/)
# target_link_libraries(${PROJECT_NAME} glfw)
# find_package(OpenGL REQUIRED)
# target_link_libraries(${PROJECT_NAME} OpenGL::GL)