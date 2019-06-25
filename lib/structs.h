//
// Created by maxim on 6/24/19.
//

#ifndef RAYTRACER_STRUCTS_H
#define RAYTRACER_STRUCTS_H

#include <stdlib.h>
#include <math.h>

typedef struct _vec3 {
    float x;
    float y;
    float z;
} vec3_t;

typedef struct _vec2 {
    float x;
    float y;
} vec2_t;

typedef struct _color {
    float r;
    float g;
    float b;
    float a;
} color_t;

vec3_t vec3(float x, float y, float z);
vec2_t vec2(float x, float y);
color_t color(float r, float g, float b, float a);

float clip(float a);
float randRange(float a, float b);
color_t randColor(float min);
color_t mixColors(color_t c1, color_t c2, float k);

#endif //RAYTRACER_STRUCTS_H
