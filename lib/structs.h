//
// Created by maxim on 6/24/19.
//

#ifndef RAYTRACER_STRUCTS_H
#define RAYTRACER_STRUCTS_H

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

float randRange(float a, float b);
color_t randColor(float min);

#endif //RAYTRACER_STRUCTS_H
