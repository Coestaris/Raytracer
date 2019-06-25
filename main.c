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

renderScene_t* scene;

void setupScene(void)
{
    scene = createScene(
            vec3(-20, 15, -15), vec3(2.5, 2.5, 2.5), .07,
            vec2(0, 0), vec2(WIN_W, WIN_H));

    pushGeometryObject(scene, createSphere(randColor(0), vec3(0, 0, 0), 1.5));
    pushGeometryObject(scene, createSphere(randColor(0), vec3(7, 0, 0), 2.5));
    pushGeometryObject(scene, createSphere(randColor(0), vec3(0, 8, 0), 2));
    pushGeometryObject(scene, createSphere(randColor(0), vec3(8, 6, 0), 2));

    pushGeometryObject(scene, createSphere(randColor(0), vec3(0, 0, 6), 2));
    pushGeometryObject(scene, createSphere(randColor(0), vec3(7, 0, 5), 2));
    pushGeometryObject(scene, createSphere(randColor(0), vec3(0, 8, 7), 2.4));
    pushGeometryObject(scene, createSphere(randColor(0), vec3(7, 8, 6), 1.5));

    pushGeometryObject(scene, createPlane(color(.5, .5, .5, 1), vec3(0, 1, 0), vec3(2.5, 0, 2.5)));

    //pushLightSource(scene, createLightSource(vec3(20, 20, -20), 0.8));
    pushLightSource(scene, createLightSource(vec3(-20, 20, 20), 2));

    scene->antialiasingIterations = 5;
    scene->antialiasingRange = 1;
    scene->environmentDarkness = 0.15;
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

    raycast_async(scene, WIN_H, drawCallback);

    freezeGraphics();

    freeScene(scene, true);
    closeGraphics();

    return 0;
}
