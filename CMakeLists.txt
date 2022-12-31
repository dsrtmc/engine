cmake_minimum_required(VERSION 3.10.0)
project(engineproject VERSION 0.1.0)

include(CTest)
enable_testing()

add_subdirectory(Engine)
add_subdirectory(Sandbox)
add_subdirectory(Game)