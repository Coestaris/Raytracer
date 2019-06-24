//
// Created by maxim on 6/24/19.
//

#ifndef RAYTRACER_GRAPHICS_H
#define RAYTRACER_GRAPHICS_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <GL/freeglut.h>

#define OVERRIDE_GL_VERSION
//#define USE_DOUBLE_BUFFERING

#ifdef OVERRIDE_GL_VERSION
#define MAJOR_GL_VERSION 3
#define MINOR_GL_VERSION 0
#endif

extern uint16_t winW;
extern uint16_t winH;

void initGraphics(int argc, const char** argv, uint16_t winW, uint16_t winH, const char* winTitle);
void freezeGraphics(void);
void closeGraphics(void);
void graphicsFlush(void);

#endif //RAYTRACER_GRAPHICS_H
