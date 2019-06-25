//
// Created by maxim on 6/24/19.
//

#include "structs.h"

vec3_t vec3(float x, float y, float z)
{
    vec3_t vec = {x, y, z};
    return vec;
}

vec2_t vec2(float x, float y)
{
    vec2_t vec = {x, y };
    return vec;
}

color_t color(float r, float g, float b, float a)
{
    color_t col  = { r, g, b, a };
    return col;
}

float randRange(float a, float b)
{
    if (a == b) return a;

    double min = a > b ? b : a;
    double max = a > b ? a : b;

    double scale = rand() / (float) RAND_MAX; /* [0, 1.0] */

    return min + scale * (max - min);
}

color_t randColor(float min)
{
    return color(randRange(min, 1),
                 randRange(min, 1),
                 randRange(min, 1),
                 1);
}

float clip(float a)
{
    a = fabsf(a);
    return a > 1 ? 1 : a;
}