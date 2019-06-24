//
// Created by maxim on 6/24/19.
//

#include "renderScene.h"

renderScene_t* createScene(vec3_t cameraPos, vec3_t cameraDir, float fov, vec2_t viewportPos, vec2_t viewportSize)
{
    renderScene_t* scene = malloc(sizeof(renderScene_t));
    scene->camera = malloc(sizeof(camera_t));
    scene->camera->position = cameraPos;
    scene->camera->direction = cameraDir;
    scene->camera->fov = fov;

    scene->screenPos = viewportPos;
    scene->screenSize = viewportSize;

    scene->geometryObjectsCount = 0;
    scene->geometryObjectsMaxCount = OBJECTS_MAX_COUNT_START;
    scene->geometryObjects = malloc(scene->geometryObjectsMaxCount * sizeof(geometryObject_t*));
    return scene;
}

void freeScene(renderScene_t* scene, uint8_t freeObjects)
{
    free(scene->camera);
    if(freeObjects)
        for(size_t i = 0; i < scene->geometryObjectsCount; i++)
            free(scene->geometryObjects[i]);
    free(scene->geometryObjects);
    free(scene);
}

void pushGeometryObject(renderScene_t* scene, geometryObject_t* object)
{
    if(scene->geometryObjectsCount == scene->geometryObjectsMaxCount - 1)
    {
        size_t newSize = (int)((float)scene->geometryObjectsCount * OBJECTS_MAX_COUNT_INCREASE);
        scene->geometryObjects = realloc(scene, newSize * sizeof(geometryObject_t*));
        scene->geometryObjectsMaxCount = newSize;
    }

    scene->geometryObjects[scene->geometryObjectsCount++] = object;
}