cmake_minimum_required(VERSION 3.10.0)
project(engine VERSION 0.1.0)

include(CTest)
enable_testing()

add_library(enginer src/Test.cpp)

# not sure if needed, TODO: read docs
# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)