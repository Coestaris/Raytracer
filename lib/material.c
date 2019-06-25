//
// Created by maxim on 6/25/19.
//

#include "material.h"

material_t* createMaterial(color_t color, float albedo, float reflectionValue)
{
    material_t* mat = malloc(sizeof(material_t));
    mat->color = color;
    mat->albedo = albedo;
    mat->reflectionValue = reflectionValue;
    return mat;
}

