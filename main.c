//
// Created by maxim on 6/24/19.
//

#include <stdio.h>
#include <unistd.h>
#include <sudo_plugin.h>

#include "lib/renderScene.h"
#include "lib/graphics.h"
#include "lib/raycaster.h"

#define WIN_W 600
#define WIN_H 600

renderScene_t* scene;

void setupScene(void)
{
    scene = createScene(
            vec3(20, 10, 20), vec3(2.5, 2.5, 2.5), .08,
            vec2(0, 0), vec2(WIN_W, WIN_H));

    pushGeometryObject(scene, createSphere(color(0, 1, 1, 1), vec3(0, 0, 0), 1.5));
    pushGeometryObject(scene, createSphere(color(1, 0, 1, 1), vec3(5, 0, 0), 2.5));
    pushGeometryObject(scene, createSphere(color(1, 1, 0, 1), vec3(0, 5, 0), 2));
    pushGeometryObject(scene, createSphere(color(1, 0, 0, 1), vec3(5, 5, 0), 1));

    pushGeometryObject(scene, createSphere(color(0, 0, 1, 1), vec3(0, 0, 5), 1));
    pushGeometryObject(scene, createSphere(color(1, 1, 1, 1), vec3(5, 0, 5), 2));
    pushGeometryObject(scene, createSphere(color(0.4, .2, 1, 1), vec3(0, 5, 5), 2.4));
    pushGeometryObject(scene, createSphere(color(0.2, 1, 0, 1), vec3(5, 5, 5), 1.5));

    scene->environmentColor = color(0, 0, 0.2, 1);
}

void drawCallback(pixelBuffer_t* buffer)
{
    //Todo pbo, or something
    glBegin(GL_POINTS);
    {
        for(size_t i = 0; i < buffer->count; i++)
        {
            glColor3f(buffer->colors[i].r, buffer->colors[i].g, buffer->colors[i].b);
            glVertex2f(buffer->pixels[i].x, buffer->pixels[i].y);
        }
    }
    glEnd();
    graphicsFlush();
    //usleep(1000);
}

int main(int argc, char const *argv[])
{
    initGraphics(argc, argv, WIN_W, WIN_H, "Simple RayTracer Sample");

    setupScene();
    double a = 0;

    while(1)
    {
        scene->camera->eye = vec3(20 * cos(a), 10, 20 * sin(a += 0.1));
        recalcCamera(scene->camera);

        raycast(scene);
        //puts("Raytracing done!");
    }
    freezeGraphics();

    freeScene(scene, true);
    closeGraphics();

    return 0;
}
