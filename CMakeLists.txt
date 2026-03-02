cmake_minimum_required(VERSION 3.23)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(ObjViewer LANGUAGES CXX C)

find_package(glfw3 REQUIRED)

add_subdirectory(external/obj-loader)

add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

add_executable(${PROJECT_NAME} main.cpp Model.cpp Shader.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ObjLoader
        glfw
        glad
)
