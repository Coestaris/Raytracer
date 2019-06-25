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
#include "material.h"

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

    material_t* material;

} geometryObject_t;

typedef struct _sphereData{
    vec3_t center;
    float radius;

} sphereData_t;

typedef struct _boxData{

} boxData_t;

typedef struct _planeData{
    vec3_t normal;
    vec3_t point;

    float radius;

    float radius2;


} planeData_t;

uint8_t intersectSphere(struct _geometryObject* this, ray_t ray, float* point);
uint8_t intersectBox(struct _geometryObject* this, ray_t ray, float* point);
uint8_t intersectPlane(struct _geometryObject* this, ray_t ray, float* point);

vec3_t normalSphere(struct _geometryObject* this, vec3_t point);
vec3_t normalBox(struct _geometryObject* this, vec3_t point);
vec3_t normalPlane(struct _geometryObject* this, vec3_t point);

geometryObject_t* createSphere(material_t* mat, vec3_t position, float radius);
geometryObject_t* createBox(material_t* mat);
geometryObject_t* createPlane(material_t* mat, vec3_t normal, vec3_t point);

void freeGeometryObject(geometryObject_t* object);

#endif //RAYTRACER_GEOMETRYOBJECT_H