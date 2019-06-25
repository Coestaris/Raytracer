//
// Created by maxim on 6/24/19.
//

#include "vecMath.h"

vec2_t vec2_add(vec2_t a, vec2_t b)
{
    return vec2(a.x + b.x, a.y + b.y);
}

vec2_t vec2_sub(vec2_t a, vec2_t b)
{
    return vec2(a.x - b.x, a.y - b.y);
}

float vec2_dot(vec2_t a, vec2_t b)
{
    return (a.x * b.x + a.y * b.y);
}

vec2_t vec2_mult(vec2_t a, float c)
{
    return vec2(a.x * c, a.y * c);
}

vec2_t vec2_div(vec2_t a, float c)
{
    return vec2(a.x / c, a.y / c);
}

vec2_t vec2_mult2(vec2_t a, float c1, float c2)
{
    return vec2(a.x * c1, a.y * c2);
}

vec2_t vec2_div2(vec2_t a, float c1, float c2)
{
    return vec2(a.x / c1, a.y / c2);
}

vec2_t vec2_normal(vec2_t a)
{
    return vec2(1, -(a.x * 1) / a.y);
}

float vec2_len(vec2_t a)
{
    return sqrtf(a.x * a.x + a.y * a.y);
}

vec2_t vec2_normalize(vec2_t a)
{
    float len = r_sqrt2(a);
    return vec2_mult(a, len);
}


vec3_t vec3_add(vec3_t a, vec3_t b)
{
    return vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

vec3_t vec3_sub(vec3_t a, vec3_t b)
{
    return vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

float vec3_dot(vec3_t a, vec3_t b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

vec3_t vec3_vmult(vec3_t a, vec3_t b)
{
    return vec3(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.z);
}

vec3_t vec3_mult(vec3_t a, float c)
{
    return vec3(a.x * c, a.y * c, a.z * c);
}

vec3_t vec3_div(vec3_t a, float c)
{
    return vec3(a.x / c, a.y / c, a.z / c);
}

vec3_t vec3_mult3(vec3_t a, float c1, float c2, float c3)
{
    return vec3(a.x * c1, a.y * c2, a.z / c3);
}

vec3_t vec3_div3(vec3_t a, float c1, float c2, float c3)
{
    return vec3(a.x / c1, a.y / c2, a.z / c3);
}

float vec3_len(vec3_t a)
{
    return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
}

vec3_t vec3_normalize(vec3_t a)
{
    float len = r_sqrt3(a);
    return vec3_mult(a, len);
}

#ifdef USE_FISQRT
float fisqrt(float number)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y = number;
    i = *(long*) &y;
    i = 0x5f3759df - (i >> 1);
    y = *(float*) &i;
    y = y * (threehalfs - (x2 * y * y));
//	y  = y * ( threehalfs - ( x2 * y * y ) );

    return y;
}
#endif