#include "ray.h"
#include "sphere.h"
#include "vector.h"

const double shadow_bias = 1e-3;

static bool scene_intersections(const Ray& ray, const std::vector<Sphere> &spheres, Vec3f &hit, Vec3f &N, Material &material) {
    double spheres_dist = std::numeric_limits<double>::max();
    for (size_t i=0; i < spheres.size(); i++) {
        double dist_i;
        if (spheres[i].intersect_with_ray(ray, dist_i) && dist_i < spheres_dist) {
            spheres_dist = dist_i;
            hit = ray.m_origin + ray.m_direction * dist_i;
            N = (hit - spheres[i].center).normalize();
            material = spheres[i].material;
        }
    }
    return spheres_dist<1000;
}

Vec3f Ray::cast(const std::vector<Sphere> &spheres, const std::vector<Light> &lights)
{
    Vec3f point, N;
    Material material;

    if (!scene_intersections(*this, spheres, point, N, material)) {
        return Vec3f(0.2, 0.7, 0.8);
    }

    float diffuse_light_intensity = 0, specular_light_intensity = 0;
    for (size_t i=0; i<lights.size(); i++) {
        Vec3f light_dir           = (lights[i].position - point).normalize();
        double light_distance     = (lights[i].position - point).norm();
        Vec3f shadow_orig = light_dir.dot(N) < 0 ? point - N*shadow_bias : point + N*shadow_bias;
        Vec3f shadow_pt, shadow_N;
        Material unused;
        Ray shadow (shadow_orig, light_dir);
        if (scene_intersections(shadow, spheres, shadow_pt, shadow_N, unused) && (shadow_pt-shadow_orig).norm() < light_distance)
        {
            continue;
        }


        diffuse_light_intensity  += lights[i].intensity * std::max(0.0, light_dir.dot(N));
        specular_light_intensity += powf(std::max(0.0, Vec3f::reflect(light_dir, N).dot(m_direction)), material.spec_exp)*lights[i].intensity;

    }
    return material.diffuse_color * material.albedo[0] * diffuse_light_intensity +
           Vec3f(1., 1., 1.) *      material.albedo[1] * specular_light_intensity;
}
