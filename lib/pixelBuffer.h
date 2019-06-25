//
// Created by maxim on 6/25/19.
//

#ifndef RAYTRACER_PIXELBUFFER_H
#define RAYTRACER_PIXELBUFFER_H

#include "structs.h"

typedef struct _pixelBuffer {
    color_t* colors;
    vec2_t* pixels;
    size_t count;

} pixelBuffer_t;

#endif //RAYTRACER_PIXELBUFFER_H
