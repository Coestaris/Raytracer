//
// Created by maxim on 6/24/19.
//

#include "geometryObject.h"

geometryObject_t* createSphere(material_t* mat, vec3_t position, float radius)
{
    geometryObject_t* object = malloc(sizeof(geometryObject_t));
    object->data = malloc(sizeof(sphereData_t));
    sphereData_t* sd = object->data;
    sd->center = position;
    sd->radius = radius;
    object->material = mat;

    object->type = sphere;
    object->normal = normalSphere;
    object->intersect = intersectSphere;
    return object;
}

geometryObject_t* createBox(material_t* mat)
{
    geometryObject_t* object = malloc(sizeof(geometryObject_t));
    object->data = malloc(sizeof(boxData_t));
    boxData_t* bd = object->data;

    object->material = mat;
    object->type = box;
    object->normal = normalBox;
    object->intersect = intersectBox;
    return object;
}

geometryObject_t* createPlane(material_t* mat, vec3_t normal, vec3_t point)
{
    geometryObject_t* object = malloc(sizeof(geometryObject_t));
    object->data = malloc(sizeof(planeData_t));
    planeData_t* pd = object->data;

    pd->normal = normal;
    pd->point = point;

    object->material = mat;
    object->type = plane;
    object->normal = normalPlane;
    object->intersect = intersectPlane;
    return object;
}

uint8_t intersectSphere(geometryObject_t* this, ray_t ray, float* t)
{
    sphereData_t* sd = this->data;

    float a = vec3_dot(ray.direction, ray.direction);
    vec3_t a_c = vec3_sub(ray.position, sd->center);
    float b = 2 * vec3_dot(ray.direction, a_c);
    float c = vec3_dot(a_c, a_c) - sd->radius * sd->radius;

    float discriminant = b * b - 4 * a * c;

    if(discriminant < 0)
        return false;

    float sq = sqrtf(discriminant);
    float t1 = (-b + sq) / (2.0 * a);
    float t2 = (-b - sq) / (2.0 * a);

    if(t1 > 1 || t2 > 1)
        return false;

    *t = t1 > t2 ? t1 : t2;
    return true;
}

uint8_t intersectBox(geometryObject_t* this, ray_t ray, float* point)
{
    boxData_t* bd = this->data;

    return false;
}

uint8_t intersectPlane(geometryObject_t* this, ray_t ray, float* point)
{
    planeData_t* pd = this->data;
    float denom = vec3_dot(pd->normal, ray.direction);
    if (denom > 1e-6) {

        float t = vec3_dot(vec3_sub(ray.position, pd->point), pd->normal) / denom;
        if(t > 0)
        {
            *point = -t;
            return true;
        }
    }

    return false;
}

vec3_t normalSphere(geometryObject_t* this, vec3_t point)
{
    sphereData_t* sd = this->data;
    return vec3_normalize(vec3_sub(point, sd->center));
}

vec3_t normalBox(geometryObject_t* this, vec3_t point)
{
    boxData_t* bd = this->data;
    return vec3(0, 0, 0);
}

vec3_t normalPlane(geometryObject_t* this, vec3_t point)
{
    planeData_t* pd = this->data;
    return pd->normal;
}


void freeGeometryObject(geometryObject_t* object)
{
    if(object->data) free(object->data);
    free(object);
}