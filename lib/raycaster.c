//
// Created by maxim on 6/24/19.
//

#include "raycaster.h"

color_t cast_ray(ray_t ray, renderScene_t* scene)
{
    float nearestDist = 9999999;
    int found = 0;

    color_t nearestColor;
    vec3_t point;

    for(size_t i = 0; i < scene->geometryObjectsCount; i++)
    {
        if(scene->geometryObjects[i]->intersect(scene->geometryObjects[i], ray, &point))
        {
            vec3_t line = vec3(ray.position.x - point.x, ray.position.y - point.y, ray.position.z - point.z);
            float len = vec3_len(line);
            if(len < nearestDist)
            {
                nearestDist = len;
                nearestColor = scene->geometryObjects[i]->color;
            }
            found = true;
        }
    }

    return found ? nearestColor : scene->environmentColor;
}

void raycast(renderScene_t* scene)
{
    glClearColor(0, 0, 0, 0);
    glBegin(GL_POINTS);
    for(float pixelX = scene->screenPos.x + 0.5 - scene->screenSize.x / 2.0; pixelX < scene->screenSize.x / 2.0 + scene->screenPos.x; pixelX += 1)
        for(float pixelY = scene->screenPos.y + 0.5 - scene->screenSize.x / 2.0; pixelY < scene->screenSize.y / 2.0 + scene->screenPos.y; pixelY += 1)
        {
            ray_t ray = getRay(scene->camera, pixelX, pixelY);
            color_t color = cast_ray(ray, scene);

            glColor3f(color.r, color.g, color.b);
            glVertex2f(pixelX + scene->screenSize.x / 2.0, pixelY + scene->screenSize.y / 2.0);
        }
    glEnd();
    graphicsFlush();
}

void raycast_async(renderScene_t* scene, size_t bufferCount, void drawCallback(pixelBuffer_t* buffer))
{
    pixelBuffer_t* buffer = malloc(sizeof(pixelBuffer_t));
    buffer->colors = malloc(sizeof(color_t) * bufferCount);
    buffer->pixels = malloc(sizeof(vec2_t) * bufferCount);
    buffer->count = bufferCount;
    buffer->scene = scene;

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