//
// Created by maxim on 6/25/19.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include <stdint.h>
#include "structs.h"

typedef struct _material {

    float reflectionValue;
    float albedo;
    color_t color;

} material_t;

material_t* createMaterial(color_t color, float albedo, float reflectionValue);

#endif //RAYTRACER_MATERIAL_H
