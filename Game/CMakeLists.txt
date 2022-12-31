cmake_minimum_required(VERSION 3.10.0)
project(game VERSION 0.1.0)

add_executable(${PROJECT_NAME}
    src/GameApp.cpp
    src/GameLayer.cpp
    src/Player.cpp
    src/Level.cpp
)

target_link_libraries(${PROJECT_NAME} engine)