//
// Created by maxim on 6/24/19.
//

#include "geometryObject.h"

geometryObject_t* createSphere(vec3_t position, float radius)
{
    geometryObject_t* object = malloc(sizeof(geometryObject_t));
    object->data = malloc(sizeof(sphereData_t));
    sphereData_t* sd = object->data;
    sd->center = position;
    sd->radius = radius;
    object->type = sphere;
    object->intersect = intersectSphere;
    return object;
}

geometryObject_t* createBox()
{
    geometryObject_t* object = malloc(sizeof(geometryObject_t));
    object->data = malloc(sizeof(boxData_t));
    boxData_t* sd = object->data;

    object->type = box;
    object->intersect = intersectBox;
    return object;
}

geometryObject_t* createPlane()
{
    geometryObject_t* object = malloc(sizeof(geometryObject_t));
    object->data = malloc(sizeof(planeData_t));
    planeData_t* sd = object->data;

    object->type = plane;
    object->intersect = intersectPlane;
    return object;
}

uint8_t intersectSphere(struct _geometryObject* this, ray_t ray, vec3_t* point)
{
    return 0;
}

uint8_t intersectBox(struct _geometryObject* this, ray_t ray, vec3_t* point)
{
    return 0;
}

uint8_t intersectPlane(struct _geometryObject* this, ray_t ray, vec3_t* point)
{
    return 0;
}