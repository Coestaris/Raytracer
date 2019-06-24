cmake_minimum_required(VERSION 3.10)
project(Raytracer C)

set(CMAKE_C_STANDARD 99)

add_executable(Raytracer main.c lib/geometryObject.h lib/structs.c lib/structs.h lib/vecMath.c lib/vecMath.h lib/raycaster.c lib/raycaster.h lib/ray.c lib/ray.h lib/geometryObject.c)
