cmake_minimum_required(VERSION 3.18)
project(Loup3D)

set(CMAKE_CXX_STANDARD 20)

message("Generated with config types: ${CMAKE_CONFIGURATION_TYPES}")

find_package(glfw3)
find_package(Threads)
find_package(OpenGL)

add_executable(Loup3D
        main.cpp
        src/Graphic.cpp
        src/Inputs.cpp
        src/Player.cpp
        src/Map.cpp
        src/Raycasting.cpp

        src/Helpers/PerlinNoise.hpp
        src/Helpers/Image.hpp)

target_link_libraries(Loup3D ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(Loup3D glfw ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES})

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    target_link_libraries(Loup3D ${GLEW_LIBRARIES})
endif()
