//
// Created by maxim on 6/24/19.
//

#include "ray.h"

ray_t getRay(camera_t* camera, float x, float y)
{
    vec3_t dir = camera->view;

    dir = vec3_add(dir, vec3_mult(camera->right, camera->fov_tan * camera->aspect * x));
    dir = vec3_add(dir, vec3_mult(camera->up, camera->fov_tan * y));
    dir = vec3_normalize(dir);

    //printf("%f %f %f\n", dir.x, dir.y, dir.z);

    ray_t result = { .position = camera->eye, .direction = dir };
    return result;
}

void recalcCamera(camera_t* camera)
{
    camera->up = vec3(0, 1, 0);

    camera->view = vec3_sub(camera->eye, camera->center);
    camera->right = vec3_vmult(camera->view, camera->up);
    camera->right = vec3_normalize(camera->right);

    camera->up = vec3_vmult(camera->right, camera->view);
    camera->up = vec3_normalize(camera->up );
    camera->fov_tan = tanf(camera->fov / 2);
    camera->aspect = winW / (float)winH;

}