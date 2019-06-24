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