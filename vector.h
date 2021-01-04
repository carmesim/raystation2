#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <cstdlib>
#ifdef _EE
#include <gsKit.h>
#endif
#include <stdint.h>

class Vec3f {
public:
    static Vec3f reflect(const Vec3f& I, const Vec3f& J);

    struct VecComponents
    {
        float x;
        float y;
        float z;
        float w;
    };

    VecComponents vector;

    float &x;
    float &y;
    float &z;

    constexpr Vec3f () : vector({}), x(vector.x), y(vector.y), z(vector.z) {}
    constexpr Vec3f (float _x, float _y, float _z) : vector({_x, _y, _z, .0f}), 
        x(vector.x), y(vector.y), z(vector.z) {}
    constexpr Vec3f (const Vec3f &other) : vector(other.vector), x(vector.x), y(vector.y), 
        z(vector.z) {}

    float norm();

    float dot(const Vec3f &other) const;

    Vec3f operator*(float k) const;

    Vec3f& operator=(const Vec3f &other);

    Vec3f normalize();

    float operator[](int index);

#ifdef _EE
    uint32_t asGsColor();
#endif
};

Vec3f operator+(const Vec3f& a, const Vec3f& b);

Vec3f operator-(const Vec3f& a, const Vec3f& b);

#endif // VECTOR_H
