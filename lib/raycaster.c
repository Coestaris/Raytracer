//
// Created by maxim on 6/24/19.
//

#include "raycaster.h"

float intersects(ray_t ray, renderScene_t* scene, geometryObject_t** nearestObject)
{
    int found = 0;
    float nearestT = 99999999;
    *nearestObject = NULL;

    for(size_t i = 0; i < scene->geometryObjectsCount; i++)
    {
        float t = 0;
        if(scene->geometryObjects[i]->intersect(scene->geometryObjects[i], ray, &t))
        {
            if(-t < nearestT)
            {
                nearestT = -t;
                *nearestObject = scene->geometryObjects[i];
            }
            found = true;
        }
    }

    if(found) return nearestT;
    else return -1;
}

color_t cast_ray(ray_t ray, renderScene_t* scene)
{
    geometryObject_t* nearestObject;
    float t = intersects(ray, scene, &nearestObject);

    if(nearestObject == NULL)
        return scene->environmentColor;

    float d = 0.05;
    for(size_t i = 0; i < scene->lightSourcesCount; i++)
    {
        vec3_t point = getRayPoint(ray, -t);
        vec3_t rayDir = vec3_normalize(vec3_sub(point, scene->lightSources[i]->position));
        ray_t lightRay = {.position = point, .direction = rayDir };

        geometryObject_t* no;
        intersects(lightRay, scene, &no);

        if(no == NULL)
        {
            vec3_t normal = nearestObject->normal(nearestObject, point);
            d += vec3_dot(rayDir, normal) * scene->lightSources[i]->brightness;
        }
    }

    return color(clip(nearestObject->color.r * d),
                 clip(nearestObject->color.g * d),
                 clip(nearestObject->color.b * d),
                 1);
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