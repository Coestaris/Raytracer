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
#include "pixelBuffer.h"

void raycast(renderScene_t* scene, void drawCallback(pixelBuffer_t* buffer));
void raycast_async(renderScene_t* scene, size_t bufferCount, void drawCallback(pixelBuffer_t* buffer));

#endif //RAYTRACER_RAYCASTER_H
