#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

#include "vector.h"
#include "sphere.h"

const Vec3f origin = Vec3f(0, 0, 0);

void render(const std::vector<Sphere> & spheres, const std::vector<Light>& lights) {
    const double width    = 320;
    const double height   = 240;
    const double fov      = M_PI/2.;
    std::vector<Vec3f> framebuffer(width*height);

    for (size_t j = 0; j<height; j++) {
        for (size_t i = 0; i<width; i++) {
            double x =  (2*(i + 0.5)/width  - 1)*tan(fov/2.)*width/height;
            double y = -(2*(j + 0.5)/height - 1)*tan(fov/2.);
            Vec3f dir = Vec3f(x, y, -1).normalize();
            Ray ray (origin, dir);
            framebuffer[i+j*width] = ray.cast(spheres, lights);
        }
    }

    // TODO: save the framebuffer to the PS2's framebuffer
    // Preferably directly, within the loop above.
}

int main() {
    Material      ivory(
                  Vec3f(0.4, 0.4, 0.3), // Color
                  Vec3f(0.6,  0.3, 0),  // Albedo
                  50.);                 // Specular exponent
    Material red_rubber (
                  Vec3f(0.3, 0.1, 0.1), // Color
                  Vec3f(0.9,  0.1, 0),  // Albedo
                  10.);                 // Specular exponent

    std::vector<Light>  lights;
    lights.push_back(Light(Vec3f(-20, 20,  20), 1.5));
    lights.push_back(Light(Vec3f( 30, 50, -25), 1.8));
    lights.push_back(Light(Vec3f( 30, 20,  30), 1.7));

    std::vector<Sphere> spheres;
    spheres.push_back(Sphere(Vec3f(-3,    0,   -16), 2,      ivory));
    spheres.push_back(Sphere(Vec3f(-1.0, -1.5, -12), 2, red_rubber));
    spheres.push_back(Sphere(Vec3f( 1.5, -0.5, -18), 3, red_rubber));
    spheres.push_back(Sphere(Vec3f( 7,    5,   -18), 4,      ivory));

    render(spheres, lights);

    return 0;
}
