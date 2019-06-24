//
// Created by maxim on 6/24/19.
//

#include "raycaster.h"

color_t cast_ray(ray_t ray, renderScene_t* scene)
{
    float nearestDist = -1;

    color_t nearestColor;
    vec3_t point;

    for(size_t i = 0; i < scene->geometryObjectsCount; i++)
    {
        if(scene->geometryObjects[i]->intersect(scene->geometryObjects[i], ray, &point))
        {
            vec3_t line = vec3(ray.position.x - point.x, ray.position.y - point.y, ray.position.z - point.z);
            float len = vec3_len(line);
            if(len > nearestDist)
            {
                nearestDist = len;
                nearestColor = scene->geometryObjects[i]->color;
            }
        }
    }

    return nearestDist == -1 ? scene->environmentColor : nearestColor;
}

void raycast_async(renderScene_t* scene, size_t bufferCount, void drawCallback(pixelBuffer_t* buffer))
{
    pixelBuffer_t* buffer = malloc(sizeof(pixelBuffer_t));
    buffer->colors = malloc(sizeof(color_t) * bufferCount);
    buffer->pixels = malloc(sizeof(vec2_t) * bufferCount);
    buffer->count = bufferCount;
    buffer->scene = scene;

    size_t bufferCounter = 0;

    float scale = tan(scene->camera->fov * 0.5);
    float imageAspectRatio = scene->screenSize.x / (float) scene->screenSize.y;
    vec3_t orig = vec3(0, 0, 0);

    for(size_t pixelX = scene->screenPos.x; pixelX < scene->screenSize.x + scene->screenPos.x; pixelX++)
        for(size_t pixelY = scene->screenPos.y; pixelY < scene->screenSize.y + scene->screenPos.y; pixelY++)
        {
            float x = (2 * (pixelX + 0.5) / (float)scene->screenSize.x - 1) * imageAspectRatio * scale;
            float y = (1 - 2 * (pixelY + 0.5) / (float)scene->screenSize.y) * scale;

            vec3_t dir = vec3(x, y, -1);
            dir = vec3_normalize(dir);

            ray_t ray = { orig, dir };

            buffer->colors[bufferCounter] = cast_ray(ray, scene);
            buffer->pixels[bufferCounter].x = pixelX;
            buffer->pixels[bufferCounter].y = pixelY;
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