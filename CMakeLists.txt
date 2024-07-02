cmake_minimum_required(VERSION 3.27.7 FATAL_ERROR)

set(PROJECT_NAME 3DgameCpp)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)