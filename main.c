//
// Created by maxim on 6/24/19.
//

#include <stdio.h>

#include "lib/renderScene.h"
#include "lib/graphics.h"

#define WIN_W 400
#define WIN_H 400

int main(int argc, char const *argv[])
{
    initGraphics(argc, argv, WIN_W, WIN_H, "Simple RayTracer Sample");

    renderScene_t* scene = createScene(
            vec3(10, 10, 10), vec3(0, 1, 0),
            vec2(10, 10), vec2(WIN_H - 10, WIN_W - 10));

    while(1);

    freeScene(scene, true);
    closeGraphics();

    return 0;
}
