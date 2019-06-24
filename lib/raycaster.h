//
// Created by maxim on 6/24/19.
//

#ifndef RAYTRACER_RAYCASTER_H
#define RAYTRACER_RAYCASTER_H

#include <stddef.h>
#include <stdbool.h>

#include "ray.h"
#include "geometryObject.h"
#include "renderScene.h"

typedef struct _pixelBuffer {
    color_t* colors;
    vec2_t* pixels;
    size_t count;

    renderScene_t* scene;

} pixelBuffer_t;

void raycast(renderScene_t* scene);
void raycast_async(renderScene_t* scene, size_t bufferCount, void drawCallback(pixelBuffer_t* buffer));

#endif //RAYTRACER_RAYCASTER_H
