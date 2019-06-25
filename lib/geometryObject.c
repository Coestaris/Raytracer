//
// Created by maxim on 6/24/19.
//

#include "geometryObject.h"

geometryObject_t* createSphere(color_t color, vec3_t position, float radius)
{
    geometryObject_t* object = malloc(sizeof(geometryObject_t));
    object->data = malloc(sizeof(sphereData_t));
    sphereData_t* sd = object->data;
    sd->center = position;
    sd->radius = radius;
    object->color = color;

    object->type = sphere;
    object->normal = normalSphere;
    object->intersect = intersectSphere;
    return object;
}

geometryObject_t* createBox(color_t color)
{
    geometryObject_t* object = malloc(sizeof(geometryObject_t));
    object->data = malloc(sizeof(boxData_t));
    boxData_t* sd = object->data;

    object->color = color;
    object->type = box;
    object->normal = normalBox;
    object->intersect = intersectBox;
    return object;
}

geometryObject_t* createPlane(color_t color)
{
    geometryObject_t* object = malloc(sizeof(geometryObject_t));
    object->data = malloc(sizeof(planeData_t));
    planeData_t* sd = object->data;

    object->color = color;
    object->type = plane;
    object->normal = normalPlane;
    object->intersect = intersectPlane;
    return object;
}

#define E 0.001

uint8_t intersectSphere(struct _geometryObject* this, ray_t ray, float* t)
{
    sphereData_t* sd = this->data;

    float a = vec3_dot(ray.direction, ray.direction);
    vec3_t a_c = vec3_sub(ray.position, sd->center);
    float b = 2 * vec3_dot(ray.direction, a_c);
    float c = vec3_dot(a_c, a_c) - sd->radius * sd->radius;

    float discriminant = b * b - 4 * a * c;
    if(discriminant < 0) return 0;

    *t = (-b - sqrt(discriminant)) / (2.0 * a);
    return 1;
}

uint8_t intersectBox(struct _geometryObject* this, ray_t ray, float* point)
{
    boxData_t* bd = this->data;

    return 0;
}

uint8_t intersectPlane(struct _geometryObject* this, ray_t ray, float* point)
{
    planeData_t* pd = this->data;
    return 0;
}

vec3_t normalSphere(struct _geometryObject* this, vec3_t point)
{
    sphereData_t* sd = this->data;
    return vec3_normalize(vec3_sub(point, sd->center));
}

vec3_t normalBox(struct _geometryObject* this, vec3_t point)
{
    boxData_t* bd = this->data;
    return vec3(0, 0, 0);
}

vec3_t normalPlane(struct _geometryObject* this, vec3_t point)
{
    planeData_t* pd = this->data;
    return vec3(0, 0, 0);
}


void freeGeometryObject(geometryObject_t* object)
{
    if(object->data) free(object->data);
    free(object);
}