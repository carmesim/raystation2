#ifndef RAY_H
#define RAY_H

#include "light.h"
#include <vector>

class Sphere;

struct Ray {
    Vec3f m_origin;
    Vec3f m_direction;

    Ray(Vec3f origin, Vec3f direction) : m_origin(origin), m_direction(direction) {};

    Vec3f cast(const std::vector<Sphere> &spheres, const std::vector<Light> &lights);

};

#endif // RAY_H
