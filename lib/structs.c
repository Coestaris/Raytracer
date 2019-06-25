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

color_t mixColors(color_t c1, color_t c2, float k)
{
    return color(
            c1.r * k + c2.r * (1 - k),
            c1.g * k + c2.g * (1 - k),
            c1.b * k + c2.b * (1 - k),
            c1.a * k + c2.a * (1 - k));
}

color_t color_clip(color_t a)
{
    return color(
            clip(a.r),
            clip(a.g),
            clip(a.b),
            clip(a.a));
}

color_t color_cadd(color_t a, color_t b)
{
    return color(
            a.r + b.r,
            a.g + b.g,
            a.b + b.b,
            a.a + a.a);
}

color_t color_cmult(color_t a, color_t b)
{
    return color(
            a.r * b.r,
            a.g * b.g,
            a.b * b.b,
            a.a * a.a);
}

color_t color_csub(color_t a, color_t b)
{
    return color(
            a.r - b.r,
            a.g - b.g,
            a.b - b.b,
            a.a - a.a);
}

color_t color_mult(color_t a, float k)
{
    return color(a.r * k, a.g * k, a.b * k, a.a * k);
}

color_t color_div(color_t a, float k)
{
    return color(a.r / k, a.g / k, a.b / k, a.a / k);
}

color_t color_sub(color_t a, float k)
{
    return color(
            a.r - k,
            a.g - k,
            a.b - k,
            a.a - k);
}

color_t color_add(color_t a, float k)
{
    return color(
            a.r + k,
            a.g + k,
            a.b + k,
            a.a + k);
}