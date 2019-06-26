//
// Created by maxim on 6/24/19.
//

#include "raycaster.h"

vec3_t reflect(vec3_t i, vec3_t n)
{
    return vec3_sub(i, vec3_mult(n, 2 * vec3_dot(i, n)));
}

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

color_t cast_ray(ray_t ray, renderScene_t* scene, int depth)
{
    geometryObject_t* nearestObject;
    float t = intersects(ray, scene, &nearestObject);

    if(depth < 0)
        return scene->environmentColor;

    if(nearestObject == NULL)
        return scene->environmentColor;

    vec3_t point = getRayPoint(ray, -t);
    color_t resultColor = color(
            scene->environmentDarkness,
            scene->environmentDarkness,
            scene->environmentDarkness,
            1);

    if(nearestObject->material->reflectionValue != 1)
    {
        vec3_t reflectedRay = reflect(ray.direction, nearestObject->normal(nearestObject, point));

        ray_t reflect = {.direction = vec3_normalize(reflectedRay), .position = point};

        resultColor = mixColors(nearestObject->material->color, cast_ray(reflect, scene, depth - 1),
                                nearestObject->material->reflectionValue);
    }

    //lighting
    for(size_t i = 0; i < scene->lightSourcesCount; i++)
    {
        vec3_t rayDir = vec3_normalize(vec3_sub(point, scene->lightSources[i]->position));
        ray_t lightRay = {.position = point, .direction = rayDir };

        geometryObject_t* no;
        intersects(lightRay, scene, &no);

        if(no == NULL)
        {
            vec3_t normal = nearestObject->normal(nearestObject, point);
            color_t intensity = getLightIntensity(scene->lightSources[i], point);

            resultColor = color_cadd(
                    resultColor,
                    color_mult(intensity, - nearestObject->material->albedo * fmin(0, vec3_dot(rayDir, normal))));
        }
        else
        {

        }
    }

    return color_clip(color_cmult(nearestObject->material->color, resultColor));
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
            color_t c = color(0, 0, 0, 0);
            for(int i = 0; i < scene->antialiasingIterations; i++)
            {
                color_t castedColor = cast_ray(
                        getRay(scene->camera,
                                pixelX + drand48() * scene->antialiasingRange,
                                pixelY + drand48() * scene->antialiasingRange), scene,
                                scene->refractionDepth);

                c = color_cadd(c, castedColor);
            }

            c = color_div(c, scene->antialiasingIterations);

            buffer->colors[bufferCounter] = c;
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