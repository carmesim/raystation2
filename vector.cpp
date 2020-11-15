#include "vector.h"

Vec3f Vec3f::reflect(const Vec3f &I, const Vec3f &N)
{
    return I - N*2.f*(I.dot(N));
}

Vec3f operator+(const Vec3f& a, const Vec3f& b)
{
    return Vec3f(a.x + b.x,
                 a.y + b.y,
                 a.z + b.z);
}

Vec3f operator-(const Vec3f& a, const Vec3f& b)
{
    return Vec3f(a.x - b.x,
                 a.y - b.y,
                 a.z - b.z);
}
