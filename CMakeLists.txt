cmake_minimum_required(VERSION 3.10)
project(Raytracer C)

set(CMAKE_C_STANDARD 99)

add_executable(Raytracer main.c lib/geometryObject.h lib/gmath.c lib/gmath.h lib/structs.c lib/structs.h lib/vecMath.c lib/vecMath.h lib/raycaster.c lib/raycaster.h lib/ray.c lib/ray.h lib/geometryObject.c lib/renderScene.c lib/renderScene.h lib/graphics.c lib/graphics.h lib/pixelBuffer.h lib/material.c lib/material.h)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

target_link_libraries(Raytracer m)
target_link_libraries(Raytracer ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})