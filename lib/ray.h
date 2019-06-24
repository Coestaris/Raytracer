//
// Created by maxim on 6/24/19.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "structs.h"
#include "vecMath.h"
#include "graphics.h"

typedef struct _ray {

    vec3_t position;
    vec3_t direction;

} ray_t;

typedef struct _camera {
    vec3_t eye;
    vec3_t center;
    float fov;

    vec3_t up;
    vec3_t right;

    vec3_t view;

    float fov_tan;
    float aspect;

} camera_t;

ray_t getRay(camera_t* camera, float x, float y);
void recalcCamera(camera_t* camera);

#endif //RAYTRACER_RAY_H
