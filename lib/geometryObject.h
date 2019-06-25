//
// Created by maxim on 6/24/19.
//

#ifndef RAYTRACER_GEOMETRYOBJECT_H
#define RAYTRACER_GEOMETRYOBJECT_H

#include <stdint.h>
#include <malloc.h>
#include <math.h>

#include "structs.h"
#include "vecMath.h"
#include "ray.h"

typedef enum _geometryObjectType {
    box,
    sphere,
    plane

} geometryObjectType_t;


typedef struct _geometryObject {

    geometryObjectType_t type;

    void* data;
    uint8_t (*intersect)(struct _geometryObject* this, ray_t ray, float* point);
    vec3_t (*normal)(struct _geometryObject* this, vec3_t point);

    color_t color;

} geometryObject_t;

typedef struct _sphereData{
    vec3_t center;
    float radius;

} sphereData_t;

typedef struct _boxData{

} boxData_t;

typedef struct _planeData{
    vec3_t a;
    vec3_t b;
    vec3_t c;
    vec3_t d;

} planeData_t;

uint8_t intersectSphere(struct _geometryObject* this, ray_t ray, float* point);
uint8_t intersectBox(struct _geometryObject* this, ray_t ray, float* point);
uint8_t intersectPlane(struct _geometryObject* this, ray_t ray, float* point);

vec3_t normalSphere(struct _geometryObject* this, vec3_t point);
vec3_t normalBox(struct _geometryObject* this, vec3_t point);
vec3_t normalPlane(struct _geometryObject* this, vec3_t point);

geometryObject_t* createSphere(color_t color, vec3_t position, float radius);
geometryObject_t* createBox(color_t color);
geometryObject_t* createPlane(color_t color);

void freeGeometryObject(geometryObject_t* object);

#endif //RAYTRACER_GEOMETRYOBJECT_H