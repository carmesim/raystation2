#ifndef MATERIAL_H
#define MATERIAL_H

#include "vector.h"

struct Material
{
    Material(const Vec3f &color) : diffuse_color(color) {}
    Material() : diffuse_color(Vec3f(1, 0, 0)), albedo(Vec3f(1, 0, 0)), spec_exp(0) {}
    Material( const Vec3f &_color, const Vec3f &_albedo, const float &spec) :
        diffuse_color(_color), albedo(_albedo), spec_exp(spec) {}
    Vec3f diffuse_color;
    Vec3f albedo;
    // Specular exponent
    double spec_exp;
};

#endif // MATERIAL_H
