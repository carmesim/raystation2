#ifndef SPHERE_H
#define SPHERE_H

#include "vector.h"
#include "material.h"
#include <limits>

class Ray;

struct Sphere {
    Vec3f center;
    double radius;
    Material material;

    Sphere(const Vec3f &_center, const double &_radius, Material &_material) :
        center(_center), radius(_radius), material(_material) {}

    bool intersect_with_ray(const Ray &ray, double &t0) const;
};


#endif // SPHERE_H
