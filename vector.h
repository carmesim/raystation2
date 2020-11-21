#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <cstdlib>
#ifdef _EE
#include <gsKit.h>
#endif
#include <stdint.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

class Vec3f {
public:
    static Vec3f reflect(const Vec3f& I, const Vec3f& J);

    float vector[4];

    float &x;
    float &y;
    float &z;

    Vec3f () : x(vector[0]), y(vector[1]), z(vector[2]) {}
    Vec3f (float _x, float _y, float _z) : x(vector[0]), y(vector[1]), z(vector[2])
    {
        vector[0] = _x;
        vector[1] = _y;
        vector[2] = _z;
    }

    float norm();

    float dot(const Vec3f &other) const;;

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
