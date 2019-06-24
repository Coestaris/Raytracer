#include <stdint.h>
#include <malloc.h>

#include "structs.h"
#include "ray.h"

typedef enum _geometryObjectType {
    box,
    sphere,
    plane

} geometryObjectType_t;


typedef struct _geometryObject {

    geometryObjectType_t type;

    void* data;
    uint8_t (*intersect)(struct _geometryObject* this, ray_t ray, vec3_t* point);

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

uint8_t intersectSphere(struct _geometryObject* this, ray_t ray, vec3_t* point);
uint8_t intersectBox(struct _geometryObject* this, ray_t ray, vec3_t* point);
uint8_t intersectPlane(struct _geometryObject* this, ray_t ray, vec3_t* point);

geometryObject_t* createSphere(vec3_t position, float radius);
geometryObject_t* createBox();
geometryObject_t* createPlane();


