# 3DgameCpp

To download and run the source cat of this project, you need to:
1) Clone the current repository
2) Add the glfw library. To do this, create an “external” directory in the root directory and clone the glfw library repository inside it.
3) Add the glad library. To do this, unpack the zip archive with the glad library into the external directory, create CMakeLists.txt inside the glad directory and enter the following commands:

cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(Glad)
add_library(glad STATIC include/glad/glad.h src/glad.c)
target_include_directories(glad PUBLIC include/)

4) In the root directory of the project, create a build directory and run the following commands in it:

cmake..
cmake --build .

5) An executable file will appear in the build directory that you can run