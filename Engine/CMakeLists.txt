cmake_minimum_required(VERSION 3.10.0)
project(engine VERSION 0.1.0)

include(CTest)
enable_testing()

# Main library
add_library(${PROJECT_NAME}
    src/Engine/Window.cpp
    src/Engine/Log.cpp

    src/OpenGL/Shader.cpp
    src/OpenGL/Renderer.cpp
    src/OpenGL/Buffer.cpp
    src/OpenGL/VertexArray.cpp

    src/Engine.h
)

target_include_directories(${PROJECT_NAME} PUBLIC src/)
target_include_directories(${PROJECT_NAME} PUBLIC src/Engine/)
target_include_directories(${PROJECT_NAME} PUBLIC src/OpenGL/)

# spdlog setup
set(spdlog_DIR vendor/spdlog/build/)
if (NOT TARGET spdlog)
    find_package(spdlog REQUIRED)
endif()
target_link_libraries(${PROJECT_NAME} spdlog::spdlog)
target_include_directories(${PROJECT_NAME} PUBLIC vendor/spdlog/include/)

# GLFW setup
set(OpenGL_GL_PREFERENCE GLVND)
add_subdirectory(vendor/glfw)
target_link_libraries(${PROJECT_NAME} glfw)
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)
target_include_directories(${PROJECT_NAME} PUBLIC vendor/glfw/include/)

# glad setup
add_subdirectory(vendor/glad)
target_link_libraries(${PROJECT_NAME} glad)
target_include_directories(${PROJECT_NAME} PUBLIC vendor/glad/include/)

# not sure if needed, TODO: read docs
# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)