//
// Created by maxim on 6/24/19.
//

#include "raycaster.h"

color_t cast_ray(ray_t ray, renderScene_t* scene)
{
    int found = 0;
    float nearestT = 99999999;
    geometryObject_t* nearestObject = NULL;

    for(size_t i = 0; i < scene->geometryObjectsCount; i++)
    {
        float t = 0;
        if(scene->geometryObjects[i]->intersect(scene->geometryObjects[i], ray, &t))
        {
            if(-t < nearestT)
            {
                nearestT = -t;
                nearestObject = scene->geometryObjects[i];
            }
            found = true;
        }
    }

    if(!found)
        return scene->environmentColor;
    else
    {
        vec3_t point = getRayPoint(ray, -nearestT);
        vec3_t normal = nearestObject->normal(nearestObject, point);
        float d = vec3_dot(ray.direction, normal);

        return color(nearestObject->color.r * fabs(d),
                     nearestObject->color.g * fabs(d),
                     nearestObject->color.b * fabs(d),
                     1);
    }
}

void raycast(renderScene_t* scene, void drawCallback(pixelBuffer_t* buffer))
{
    size_t bufferCount = scene->screenSize.x * scene->screenSize.y;
    raycast_async(scene, bufferCount, drawCallback);
}

void raycast_async(renderScene_t* scene, size_t bufferCount, void drawCallback(pixelBuffer_t* buffer))
{
    pixelBuffer_t* buffer = malloc(sizeof(pixelBuffer_t));
    buffer->colors = malloc(sizeof(color_t) * bufferCount);
    buffer->pixels = malloc(sizeof(vec2_t) * bufferCount);
    buffer->count = bufferCount;

    size_t bufferCounter = 0;

    for(float pixelX = scene->screenPos.x + 0.5 - scene->screenSize.x / 2.0; pixelX < scene->screenSize.x / 2.0 + scene->screenPos.x; pixelX += 1)
        for(float pixelY = scene->screenPos.y + 0.5 - scene->screenSize.x / 2.0; pixelY < scene->screenSize.y / 2.0 + scene->screenPos.y; pixelY += 1)
        {
            ray_t ray = getRay(scene->camera, pixelX, pixelY);

            buffer->colors[bufferCounter] = cast_ray(ray, scene);
            buffer->pixels[bufferCounter].x = pixelX + scene->screenSize.x / 2.0;
            buffer->pixels[bufferCounter].y = pixelY + scene->screenSize.y / 2.0;
            bufferCounter++;

            if(bufferCounter == bufferCount)
            {
                drawCallback(buffer);
                bufferCounter = 0;
            }
        }

    if(bufferCounter != 0)
    {
        buffer->count = bufferCounter - 1;
        drawCallback(buffer);
    }

    free(buffer->pixels);
    free(buffer->colors);
    free(buffer);
}