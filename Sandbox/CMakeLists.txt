cmake_minimum_required(VERSION 3.10.0)
project(sandbox VERSION 0.1.0)

add_library(${PROJECT_NAME}
    src/Sandbox.cpp
    src/tests/Test2D.cpp
)
