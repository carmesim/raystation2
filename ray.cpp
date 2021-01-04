#include "ray.h"
#include "sphere.h"
#include "vector.h"

const float shadow_bias = 1e-3;

static bool scene_intersections(const Ray& ray, const std::vector<Sphere> &spheres, Vec3f &hit, Vec3f &N, Material &material) {
    float spheres_dist = std::numeric_limits<float>::max();
    for (const auto & sphere : spheres) {
        float dist_i;
        if (sphere.intersect_with_ray(ray, dist_i) && dist_i < spheres_dist) {
            spheres_dist = dist_i;
            hit = ray.m_origin + ray.m_direction * dist_i;
            N = (hit - sphere.center).normalize();
            material = sphere.material;
        }
    }
    return spheres_dist<1000;
}

Vec3f Ray::cast(const std::vector<Sphere> &spheres, const std::vector<Light> &lights)
{
    Vec3f point;
Vec3f N;
    Material material;

    if (!scene_intersections(*this, spheres, point, N, material)) {
        return Vec3f(0.2f, 0.7f, 0.8f);
    }

    float diffuse_light_intensity = 0;
float specular_light_intensity = 0;
    for (const auto & light : lights) {
        Vec3f light_dir           = (light.position - point).normalize();
        float light_distance     = (light.position - point).norm();
        Vec3f shadow_orig = light_dir.dot(N) < 0 ? point - N*shadow_bias : point + N*shadow_bias;
        Vec3f shadow_pt;
Vec3f shadow_N;
        Material unused;
        Ray shadow (shadow_orig, light_dir);
        if (scene_intersections(shadow, spheres, shadow_pt, shadow_N, unused) && (shadow_pt-shadow_orig).norm() < light_distance)
        {
            continue;
        }


        diffuse_light_intensity  += light.intensity * std::max(0.0f, light_dir.dot(N));
        specular_light_intensity += powf(std::max(0.0f, Vec3f::reflect(light_dir, N).dot(m_direction)), material.spec_exp)*light.intensity;

    }
    return material.diffuse_color * material.albedo[0] * diffuse_light_intensity +
           Vec3f(1.f, 1.f, 1.f) *      material.albedo[1] * specular_light_intensity;
}
