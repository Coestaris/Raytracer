//
// Created by maxim on 6/24/19.
//

#ifndef RAYTRACER_RENDERSCENE_H
#define RAYTRACER_RENDERSCENE_H

#include <stddef.h>
#include <stdint.h>

#include "structs.h"
#include "geometryObject.h"
#include "ray.h"

#define OBJECTS_MAX_COUNT_START 5
#define OBJECTS_MAX_COUNT_INCREASE 1.5

typedef struct _lightSource {
    vec3_t position;
    float brightness;

} lightSource_t;

typedef struct _renderScene {
    camera_t* camera;

    vec2_t screenPos;
    vec2_t screenSize;

    size_t geometryObjectsCount;
    size_t geometryObjectsMaxCount;
    geometryObject_t** geometryObjects;

    size_t lightSourcesCount;
    size_t lightSourcesMaxCount;
    lightSource_t** lightSources;

    color_t environmentColor;

    float environmentDarkness;
    size_t antialiasingIterations;
    float antialiasingRange;

} renderScene_t;

renderScene_t* createScene(vec3_t cameraPos, vec3_t cameraDir, float fov, vec2_t viewportPos, vec2_t viewportSize);
void freeScene(renderScene_t* scene, uint8_t freeObjects);
void pushGeometryObject(renderScene_t* scene, geometryObject_t* object);
lightSource_t* createLightSource(vec3_t position, float brightness);
void pushLightSource(renderScene_t* scene, lightSource_t* ls);

#endif //RAYTRACER_RENDERSCENE_H
