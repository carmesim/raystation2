#include "ray.h"
#include "sphere.h"

bool Sphere::intersect_with_ray(const Ray & ray, float &t0) const {
    Vec3f L = center - ray.m_origin;
    float tca = L.dot(ray.m_direction);
    float d2 = L.dot(L) - tca*tca;
    if (d2 > radius*radius) return false;
    float thc = sqrtf(radius*radius - d2);
    t0       = tca - thc;
    float t1 = tca + thc;
    if (t0 < 0) t0 = t1;
    return t0 >= 0;
}
