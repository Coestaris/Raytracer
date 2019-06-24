//
// Created by maxim on 6/24/19.
//

#ifndef RAYTRACER_GRAPHICS_H
#define RAYTRACER_GRAPHICS_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <GL/freeglut.h>

void initGraphics(int argc, const char** argv, uint16_t winW, uint16_t winH, const char* winTitle);
void freezeGraphics();
void closeGraphics();

#endif //RAYTRACER_GRAPHICS_H
