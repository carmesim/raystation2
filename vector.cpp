#include "vector.h"

Vec3f Vec3f::reflect(const Vec3f &I, const Vec3f &N)
{
    return I - N*2.f*(I.dot(N));
}

float Vec3f::norm() {
    return sqrt(this->x * this->x +
                this->y * this->y +
                this->z * this->z);
}

float Vec3f::dot(const Vec3f & other) const {
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

Vec3f & Vec3f::operator=(const Vec3f & other)
{
    vector[0] = other.vector[0];
    vector[1] = other.vector[1];
    vector[2] = other.vector[2];
    vector[3] = other.vector[3];

    return *this;
}

Vec3f Vec3f::normalize() {
    return (*this) * (1/this->norm());
}

float Vec3f::operator[](int index)
{
    if (index > 3 || index < 0)
    {
        return -0.0f;
    }

    return vector[index];
}
#ifdef _EE
uint32_t Vec3f::asGsColor()
{
    unsigned char r = static_cast<unsigned char>(255.0 * MAX(0.0, MIN(1.0, x)));
    unsigned char g = static_cast<unsigned char>(255.0 * MAX(0.0, MIN(1.0, y)));
    unsigned char b = static_cast<unsigned char>(255.0 * MAX(0.0, MIN(1.0, z)));
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
