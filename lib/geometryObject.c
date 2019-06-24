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
    sphereData_t* sd = this->data;

    double cx = sd->center.x;
    double cy = sd->center.y;
    double cz = sd->center.z;

    double px = ray.position.x;
    double py = ray.position.y;
    double pz = ray.position.z;

    double vx = ray.direction.x;
    double vy = ray.direction.y;
    double vz = ray.direction.z;

    vec3_t linePoint0 = ray.position;
    vec3_t linePoint1 = vec3_add(ray.position, ray.direction);

    double A = vx * vx + vy * vy + vz * vz;
    double B = 2.0 * (px * vx + py * vy + pz * vz - vx * cx - vy * cy - vz * cz);
    double C = px * px - 2 * px * cx + cx * cx + py * py - 2 * py * cy + cy * cy +
               pz * pz - 2 * pz * cz + cz * cz - sd->radius * sd->radius;

    double D = B * B - 4 * A * C;

    if (D < 0)
    {
        return 0;
    }

    double t1 = (-B - sqrt(D)) / (2.0 * A);

    vec3_t solution1 = vec3(linePoint0.x * (1 - t1) + t1 * linePoint1.x,
                            linePoint0.y * (1 - t1) + t1 * linePoint1.y,
                            linePoint0.z * (1 - t1) + t1 * linePoint1.z);
    if (D == 0)
    {
        *point = solution1;
        return 1;
    }

    double t2 = (-B + sqrt(D)) / (2.0 * A);
    vec3_t solution2 = vec3(linePoint0.x * (1 - t2) + t2 * linePoint1.x,
                            linePoint0.y * (1 - t2) + t2 * linePoint1.y,
                            linePoint0.z * (1 - t2) + t2 * linePoint1.z);

    if (fabs(t1 - 0.5) < fabs(t2 - 0.5))
    {
        *point = solution1;
    }
    else
    {
        *point = solution2;
    }

    return 1;
}

uint8_t intersectBox(struct _geometryObject* this, ray_t ray, vec3_t* point)
{
    return 0;
}

uint8_t intersectPlane(struct _geometryObject* this, ray_t ray, vec3_t* point)
{
    return 0;
}

void freeGeometryObject(geometryObject_t* object)
{
    if(object->data) free(object->data);
    free(object);
}