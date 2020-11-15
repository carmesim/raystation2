#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "vector.h"

struct Light {
    Light(const Vec3f &p, const float &i) : position(p), intensity(i) {}
    Vec3f position;
    float intensity;
};

#endif // LIGHT_HPP
