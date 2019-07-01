//
// Created by maxim on 6/24/19.
//

#include <stdio.h>
#include <unistd.h>

#include "lib/renderScene.h"
#include "lib/graphics.h"
#include "lib/raycaster.h"

#define WIN_W 600
#define WIN_H 600
#define SPHERE_COUNT 8

renderScene_t* scene;

void setupScene(void)
{
    scene = createScene(
            vec3(-20, 15, -15), vec3(2.5, 2.5, 2.5), .07,
            vec2(0, 0), vec2(WIN_W, WIN_H));

    vec3_t coordinates[SPHERE_COUNT] = {
        vec3(0, 0, 0), vec3(7, 0, 0), vec3(0, 8, 0), vec3(8, 6, 0),
        vec3(0, 0, 6), vec3(7, 0, 5), vec3(0, 8, 7), vec3(7, 8, 6),
    };

    float radius[SPHERE_COUNT] = {
        1.5, 2.5, 2,   2,
        2,   2,   2.4, 1.5,
    };

    material_t* materials[SPHERE_COUNT] = {
        createMaterial(randColor(0), 2, 0.5), createMaterial(randColor(0), 2, 0.5),
        createMaterial(randColor(0), 2, 0.5), createMaterial(randColor(0), 2, 0.5),
        createMaterial(randColor(0), 2, 0.5), createMaterial(randColor(0), 2, 0.5),
        createMaterial(randColor(0), 2, 0.5), createMaterial(randColor(0), 2, 0.5),
    };
    material_t* planeMaterial = createMaterial(color(.5, .5, .5, 1), 2, 0.5);

    for(size_t i = 0; i < SPHERE_COUNT; i++)
        pushGeometryObject(scene, createSphere(materials[i], coordinates[i], radius[i]));
    pushGeometryObject(scene, createPlane(planeMaterial, vec3(0, 1, 0), vec3(2.5, 0, 2.5)));

    pushLightSource(scene, createLightSource(vec3(20, 20, -20), color(1, 1, 1, 1), 50));
    pushLightSource(scene, createLightSource(vec3(-20, 20, 20), color(1, 1, 1, 1), 100));

    scene->MSAAFactor = 1;

    scene->antialiasingIterations = 1;
    scene->antialiasingRange = 0;

    scene->refractionDepth = 5;
    scene->environmentDarkness = 0.05;
    scene->environmentColor = color(0, 0, 0, 1);
}

void drawCallback(pixelBuffer_t* buffer)
{
    surfDrawPixels(buffer);
    graphicsFlush();
}

int main(int argc, char const *argv[])
{
    initGraphics(argc, argv, WIN_W, WIN_H, "Simple RayTracer Sample");

    setupScene();
    float a = 0;

    raycast_async(scene, WIN_H * 3, drawCallback);

    freezeGraphics();

    freeScene(scene, true);
    closeGraphics();

    return 0;
}
