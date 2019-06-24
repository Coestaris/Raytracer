//
// Created by maxim on 6/24/19.
//

#include <stdio.h>

#include "lib/renderScene.h"
#include "lib/graphics.h"
#include "lib/raycaster.h"

#define WIN_W 400
#define WIN_H 400

renderScene_t* scene;

void setupScene(void)
{
    scene = createScene(
            vec3(10, 10, 10), vec3(0, 1, 0), 0.5,
            vec2(10, 10), vec2(WIN_H - 10, WIN_W - 10));

    pushGeometryObject(scene, createSphere(color(0, 1, 1, 1), vec3(1, 1, 1), 3));
    pushGeometryObject(scene, createSphere(color(1, 0, 1, 1), vec3(2, 1, 1), 2));
    pushGeometryObject(scene, createSphere(color(1, 1, 0, 1), vec3(1, 2, 1), 2));
    pushGeometryObject(scene, createSphere(color(1, 0, 0, 1), vec3(5, 1, -1), 4));

    scene->environmentColor = color(0, 0, 0, 1);
}

void drawCallback(pixelBuffer_t* buffer)
{
    //Todo pbo, or something
    glBegin(GL_POINTS);
    {
        for(size_t i = 0; i < buffer->count; i++)
        {
            glColor3f(buffer->colors[i].r, buffer->colors[i].g, buffer->colors[i].b);
            glVertex2i(buffer->pixels[i].x, buffer->pixels[i].y);
        }
    }
    glEnd();
}

int main(int argc, char const *argv[])
{
    initGraphics(argc, argv, WIN_W, WIN_H, "Simple RayTracer Sample");

    setupScene();

    raycast_async(scene, 1000, drawCallback);

    freezeGraphics();

    freeScene(scene, true);
    closeGraphics();

    return 0;
}
