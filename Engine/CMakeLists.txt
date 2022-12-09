cmake_minimum_required(VERSION 3.10.0)
project(engine VERSION 0.1.0)

include(CTest)
enable_testing()

# Main library
add_library(${PROJECT_NAME}
    src/Engine/Window.cpp
    src/Engine/Log.cpp
    src/Engine/OrthographicCamera.cpp
    src/Engine/Input.cpp

    src/Engine/Events/Event.h
    src/Engine/Events/KeyEvent.h
    src/Engine/Events/ApplicationEvent.h

    src/Engine/UI/UILayer.cpp

    src/OpenGL/Shader.cpp
    src/OpenGL/Renderer.cpp
    src/OpenGL/Buffer.cpp
    src/OpenGL/VertexArray.cpp
    src/OpenGL/Texture.cpp

    src/Engine.h
)

target_include_directories(${PROJECT_NAME} PUBLIC src/)
target_include_directories(${PROJECT_NAME} PUBLIC src/Engine/)
target_include_directories(${PROJECT_NAME} PUBLIC src/Engine/Events/)
target_include_directories(${PROJECT_NAME} PUBLIC src/Engine/UI/)
target_include_directories(${PROJECT_NAME} PUBLIC src/OpenGL/)

target_precompile_headers(${PROJECT_NAME} PUBLIC src/enpch.h)

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

# glm setup
add_subdirectory(vendor/glm)
target_link_libraries(${PROJECT_NAME} glm)
target_include_directories(${PROJECT_NAME} PUBLIC
    vendor/glm/glm/
    vendor/glm/glm/gtc/
)

# stb image setup
add_subdirectory(vendor/stb_image)
target_link_libraries(${PROJECT_NAME} stb_image)
target_include_directories(${PROJECT_NAME} PUBLIC vendor/stb_image)

# imgui setup
set(imgui_PATH vendor/imgui)
file(GLOB imgui_SOURCES
    ${imgui_PATH}/*.cpp
    ${imgui_PATH}/backends/imgui_impl_glfw.cpp
    ${imgui_PATH}/backends/imgui_impl_opengl3.cpp
)
add_library(imgui STATIC ${imgui_SOURCES})
target_include_directories(imgui PUBLIC ${imgui_PATH}/ ${imgui_PATH}/backends/)
target_link_libraries(${PROJECT_NAME} imgui)