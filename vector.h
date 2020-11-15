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
    double x, y, z;
    Vec3f () : x(0), y(0), z(0) {}
    Vec3f (double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

    double norm();

    double dot(const Vec3f & other) const;;

    Vec3f operator*(double k) const;

    Vec3f normalize();

    double operator[](int index);

#ifdef _EE
    uint32_t asGsColor();
#endif
};

Vec3f operator+(const Vec3f& a, const Vec3f& b);

Vec3f operator-(const Vec3f& a, const Vec3f& b);

#endif // VECTOR_H
