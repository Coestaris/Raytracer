//
// Created by maxim on 6/24/19.
//

#ifndef RAYTRACER_GRAPHICS_H
#define RAYTRACER_GRAPHICS_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <memory.h>
#include <GL/freeglut.h>

#include "pixelBuffer.h"

#define OVERRIDE_GL_VERSION
//#define USE_DOUBLE_BUFFERING
//#define USE_FBO


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

void surfDrawPixels(pixelBuffer_t* buffer);
#ifdef USE_FBO
void surfInit();
int surfClear();
int surfFree();
void surfBind();
void surfDraw();
#endif

#endif //RAYTRACER_GRAPHICS_H
