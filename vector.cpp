#include "vector.h"

Vec3f Vec3f::reflect(const Vec3f &I, const Vec3f &J)
{
    return I - J*2.f*(I.dot(J));
}

float Vec3f::norm() {
    return std::sqrt(this->x * this->x +
                     this->y * this->y +
                     this->z * this->z);
}

float Vec3f::dot(const Vec3f & other) const {
#ifdef USE_VU
    VecComponents mulResult;
    Vec3f &nonConstThis = const_cast<Vec3f &>(*this);

    asm __volatile__ (
    "lqc2 vf1, 0(%1)\n"
    "lqc2 vf2, 0(%2)\n"
    "vmul.xyzw vf3, vf1, vf2\n"
    "sqc2 vf3, 0(%0)\n"
    : "=r" (mulResult) : "r" (nonConstThis.vector), "r" (other.vector));

    return mulResult.x + mulResult.y + mulResult.z;
#endif
    return  this->x * other.x +
            this->y * other.y +
            this->z * other.z;
}

Vec3f Vec3f::operator*(float k) const
{
    return Vec3f(this->x * k,
                 this->y * k,
                 this->z * k);
}

Vec3f &Vec3f::operator=(const Vec3f & other)
{
    vector.x = other.vector.x;
    vector.y = other.vector.y;
    vector.z = other.vector.z;
    vector.w = other.vector.w;

    return *this;
}

Vec3f Vec3f::normalize() {
    return (*this) * (1/this->norm());
}

float Vec3f::operator[](int index)
{
    if (index == 0) return vector.x;
    if (index == 1) return vector.y;
    if (index == 2) return vector.z;
    if (index == 3) return vector.w;
    return -0.0f;
}
#ifdef _EE
uint32_t Vec3f::asGsColor()
{
    unsigned char r = static_cast<unsigned char>(255.0f * std::max(.0f, std::min(1.f, x)));
    unsigned char g = static_cast<unsigned char>(255.0f * std::max(.0f, std::min(1.f, y)));
    unsigned char b = static_cast<unsigned char>(255.0f * std::max(.0f, std::min(1.f, z)));
    return GS_SETREG_RGBA(r, g, b, 0xFF);
}
#endif
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
