cmake_minimum_required(VERSION 3.10.0)
project(sandbox VERSION 0.1.0)

add_executable(${PROJECT_NAME}
    src/Sandbox.cpp
    src/TestLayer.cpp
)

target_link_libraries(${PROJECT_NAME} engine)