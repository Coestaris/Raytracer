//
// Created by maxim on 6/24/19.
//

#include "renderScene.h"

renderScene_t* createScene(vec3_t cameraPos, vec3_t cameraDir, float fov, vec2_t viewportPos, vec2_t viewportSize)
{
    renderScene_t* scene = malloc(sizeof(renderScene_t));
    scene->camera = malloc(sizeof(camera_t));
    scene->camera->eye = cameraPos;
    scene->camera->center = cameraDir;
    scene->camera->fov = fov;

    recalcCamera(scene->camera);

    scene->screenPos = viewportPos;
    scene->screenSize = viewportSize;

    scene->geometryObjectsCount = 0;
    scene->geometryObjectsMaxCount = OBJECTS_MAX_COUNT_START;
    scene->geometryObjects = malloc(scene->geometryObjectsMaxCount * sizeof(geometryObject_t*));

    scene->lightSourcesCount = 0;
    scene->lightSourcesMaxCount = OBJECTS_MAX_COUNT_START;
    scene->lightSources = malloc(scene->lightSourcesMaxCount * sizeof(lightSource_t*));
    return scene;
}

void freeScene(renderScene_t* scene, uint8_t freeObjects)
{
    free(scene->camera);
    if(freeObjects)
    {
        for (size_t i = 0; i < scene->geometryObjectsCount; i++)
            free(scene->geometryObjects[i]);
        for (size_t i = 0; i < scene->lightSourcesCount; i++)
            free(scene->lightSources[i]);
    }
    free(scene->geometryObjects);
    free(scene);
}

void pushGeometryObject(renderScene_t* scene, geometryObject_t* object)
{
    if(scene->geometryObjectsCount == scene->geometryObjectsMaxCount - 1)
    {
        size_t newSize = (int)((float)scene->geometryObjectsCount * OBJECTS_MAX_COUNT_INCREASE);
        scene->geometryObjects = realloc(scene->geometryObjects, newSize * sizeof(geometryObject_t*));
        scene->geometryObjectsMaxCount = newSize;
    }

    scene->geometryObjects[scene->geometryObjectsCount++] = object;
}

lightSource_t* createLightSource(vec3_t position, float brightness)
{
    lightSource_t* ls = malloc(sizeof(lightSource_t));
    ls->position = position;
    ls->brightness = brightness;
    return ls;
}

void pushLightSource(renderScene_t* scene, lightSource_t* ls)
{
    if(scene->lightSourcesCount == scene->lightSourcesMaxCount- 1)
    {
        size_t newSize = (int)((float)scene->lightSourcesCount * OBJECTS_MAX_COUNT_INCREASE);
        scene->lightSources = realloc(scene->lightSources, newSize * sizeof(lightSource_t*));
        scene->lightSourcesMaxCount = newSize;
    }

    scene->lightSources[scene->lightSourcesCount++] = ls;
}