#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <cstdlib>

class Vec3f {
public:
    static Vec3f reflect(const Vec3f& I, const Vec3f& J);
    double x, y, z;
    Vec3f () : x(0), y(0), z(0) {}
    Vec3f (double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

    double norm () {
        return sqrt(this->x * this->x +
                    this->y * this->y +
                    this->z * this->z);
    }

    double dot ( const Vec3f & other) const {
        return  this->x * other.x +
                this->y * other.y +
                this->z * other.z;
    };

    Vec3f operator*( double k) const
    {
        return Vec3f(this->x * k,
                     this->y * k,
                     this->z * k);
    }

    Vec3f normalize () {
        return (*this) * (1/this->norm());
    }

    double operator[] (int index)
    {
        if (index > 2 || index < 0)
        {
            // TODO: proper exception or something
            std::exit(-1);
        }
        if (index == 0) {
            return this->x;
        } else if (index == 1) {
            return this->y;
        }
        return this->z;
    }
};

Vec3f operator+(const Vec3f& a, const Vec3f& b);

Vec3f operator-(const Vec3f& a, const Vec3f& b);






#endif // VECTOR_H
