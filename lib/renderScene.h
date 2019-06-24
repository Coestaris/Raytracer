//
// Created by maxim on 6/24/19.
//

#ifndef RAYTRACER_RENDERSCENE_H
#define RAYTRACER_RENDERSCENE_H

#include <stddef.h>
#include <stdint.h>

#include "structs.h"
#include "raycaster.h"

#define OBJECTS_MAX_COUNT_START 5
#define OBJECTS_MAX_COUNT_INCREASE 1.5

typedef struct _camera {
    vec3_t position;
    vec3_t direction;

} camera_t;

typedef struct _renderScene {
    camera_t* camera;

    vec2_t screenPos;
    vec2_t screenSize;

    size_t geometryObjectsCount;
    size_t geometryObjectsMaxCount;
    geometryObject_t** geometryObjects;

} renderScene_t;

renderScene_t* createScene(vec3_t cameraPos, vec3_t cameraDir, vec2_t viewportPos, vec2_t viewportSize);
void freeScene(renderScene_t* scene, uint8_t freeObjects);
void pushGeometryObject(renderScene_t* scene, geometryObject_t* object);

#endif //RAYTRACER_RENDERSCENE_H
