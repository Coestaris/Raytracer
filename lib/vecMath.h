//
// Created by maxim on 6/24/19.
//

#ifndef RAYTRACER_VECMATH_H
#define RAYTRACER_VECMATH_H

#include <math.h>

#include "structs.h"

#define USE_FISQRT

vec2_t vec2_add(vec2_t a, vec2_t b);
vec2_t vec2_sub(vec2_t a, vec2_t b);
float vec2_dot(vec2_t a, vec2_t b);
vec2_t vec2_mult(vec2_t a, float c);
vec2_t vec2_div(vec2_t a, float c);
vec2_t vec2_mult2(vec2_t a, float c1, float c2);
vec2_t vec2_div2(vec2_t a, float c1, float c2);
vec2_t vec2_normal(vec2_t a);
float vec2_len(vec2_t a);
vec2_t vec2_normalize(vec2_t a);

vec3_t vec3_add(vec3_t a, vec3_t b);
vec3_t vec3_sub(vec3_t a, vec3_t b);
float vec3_dot(vec3_t a, vec3_t b);
vec3_t vec3_vmult(vec3_t a, vec3_t b);
vec3_t vec3_mult(vec3_t a, float c);
vec3_t vec3_div(vec3_t a, float c);
vec3_t vec3_mult3(vec3_t a, float c1, float c2, float c3);
vec3_t vec3_div3(vec3_t a, float c1, float c2, float c3);
float vec3_len(vec3_t a);
vec3_t vec3_normalize(vec3_t a);


#ifdef USE_FISQRT
float fisqrt(float number);
#define r_sqrt2(a) fisqrt(a.x * a.x + a.y * a.y)
#define r_sqrt3(a) fisqrt(a.x * a.x + a.y * a.y + a.z * a.z)
#else
#define r_sqrt2(a) 1 / vec2_len(a)
#define r_sqrt3(a) 1 / vec3_len(a)
#endif

#endif //RAYTRACER_VECMATH_H
